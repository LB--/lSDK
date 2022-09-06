#ifndef lSDK_FusionMenu_HeaderPlusPlus
#define lSDK_FusionMenu_HeaderPlusPlus

#include <cstdint>
#include <memory>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <variant>
#include <vector>

#include "FusionAPI.hpp"
#include "lSDK.hpp"
#include "lSDK/WindowsUtilities.hpp"

namespace lSDK
{
	template<FusionAceType menu_type, template<typename> typename Container = std::vector>
	struct FusionMenu final
	{
		static constexpr FusionAceType menu_type_v = menu_type;
		static constexpr auto first_menu_id() noexcept
		-> std::uint32_t
		{
			if constexpr(menu_type == FusionAceType::Action)
			{
				return FUSION_MENU_ACTIONS_FIRST;
			}
			else if constexpr(menu_type == FusionAceType::Condition)
			{
				return FUSION_MENU_CONDITIONS_FIRST;
			}
			else if constexpr(menu_type == FusionAceType::Expression)
			{
				return FUSION_MENU_EXPRESSIONS_FIRST;
			}
		}
		static constexpr auto last_menu_id() noexcept
		-> std::uint32_t
		{
			if constexpr(menu_type == FusionAceType::Action)
			{
				return FUSION_MENU_ACTIONS_LAST;
			}
			else if constexpr(menu_type == FusionAceType::Condition)
			{
				return FUSION_MENU_CONDITIONS_LAST;
			}
			else if constexpr(menu_type == FusionAceType::Expression)
			{
				return FUSION_MENU_EXPRESSIONS_LAST;
			}
		}

		struct ExtensionData final
		{
			using Data_t = std::int16_t;

			constexpr ExtensionData() noexcept = delete;
			constexpr ExtensionData(Data_t const from)
			: data{from}
			{
				if(from < 0 || from > static_cast<Data_t>(last_menu_id() - first_menu_id()))
				{
					throw std::out_of_range{"FusionMenu ExtensionData must be in the range [0, "+std::to_string(last_menu_id() - first_menu_id())+"], provided value was "+std::to_string(from)};
				}
			}

			constexpr operator Data_t() const noexcept
			{
				return data;
			}

			constexpr auto to_menu_id() const noexcept
			-> std::uint32_t
			{
				return first_menu_id() + data;
			}
			static constexpr auto from_menu_id(std::uint32_t const menu_id)
			-> Data_t
			{
				if(menu_id >= first_menu_id() && menu_id <= last_menu_id())
				{
					return static_cast<Data_t>(menu_id - first_menu_id());
				}
				throw std::out_of_range{"FusionMenu menu_id must be in the range ["+std::to_string(first_menu_id())+", "+std::to_string(last_menu_id())+"], provided value was "+std::to_string(menu_id)};
			}

		private:
			Data_t data;
		};
		struct Separator final
		{
		};
		using MenuText_v = std::variant<string_t, char_t const*, ::UINT /*resource ID*/>;
		struct Item final
		{
			ExtensionData data;
			MenuText_v text;
			bool enabled = true;
			constexpr Item(ExtensionData data, string_t            text     , bool enabled = true) noexcept : data{std::move(data)}, text(std::in_place_type<string_t>, std::move(text)), enabled{enabled} {}
			constexpr Item(ExtensionData data, char_t const* const text     , bool enabled = true) noexcept : data{std::move(data)}, text(std::in_place_type<char_t const*>,      text) , enabled{enabled} {}
			constexpr Item(ExtensionData data, ::UINT const text_resource_id, bool enabled = true) noexcept : data{std::move(data)}, text(std::in_place_type<::UINT>, text_resource_id) , enabled{enabled} {}
		};
		struct Submenu;
		using variant = std::variant<Separator, Item, Submenu>;
		using Items_t = Container<variant>;
		struct Submenu final
		{
			MenuText_v name;
			Items_t items;
			bool enabled = true;
			constexpr Submenu(string_t            name     , Items_t items, bool enabled = true) noexcept : name(std::in_place_type<string_t>, std::move(name)), items(std::move(items)), enabled{enabled} {}
			constexpr Submenu(char_t const* const name     , Items_t items, bool enabled = true) noexcept : name(std::in_place_type<char_t const*>,      name) , items(std::move(items)), enabled{enabled} {}
			constexpr Submenu(::UINT const name_resource_id, Items_t items, bool enabled = true) noexcept : name(std::in_place_type<::UINT>, name_resource_id) , items(std::move(items)), enabled{enabled} {}
		};
		Items_t items;

		struct MenuTextConverter final
		{
			MENUITEMINFO &info;
			string_t &temp_string;
			void operator()(string_t const &s) const noexcept
			{
				info.dwTypeData = const_cast<::LPWSTR>(s.data());
			}
			void operator()(char_t const *s) const noexcept
			{
				info.dwTypeData = const_cast<::LPWSTR>(s);
			}
			void operator()(::UINT const resource_id) const
			{
				temp_string.assign(get_resource_string(resource_id));
				info.dwTypeData = temp_string.data();
			}
		};
		using Handle_t = LSDK_UNIQUE_HANDLE(DestroyMenu);
		static void append(Handle_t &handle, Items_t const &items)
		{
			string_t temp_string;
			for(auto const &v : items)
			{
				MENUITEMINFO info {sizeof(MENUITEMINFO), MIIM_FTYPE};
				Handle_t temp_menu {nullptr};
				std::visit([&](auto const &item)
				{
					using Item_t = std::decay_t<decltype(item)>;
					static_assert(std::is_same_v<Item_t, Separator> || std::is_same_v<Item_t, Item> || std::is_same_v<Item_t, Submenu>);
					if constexpr(std::is_same_v<Item_t, Separator>)
					{
						info.fType = MFT_SEPARATOR;
					}
					else if constexpr(std::is_same_v<Item_t, Item>)
					{
						info.fMask |= MIIM_STATE|MIIM_STRING|MIIM_ID;
						info.fType = MFT_STRING;
						if(item.enabled)
						{
							info.fState = MFS_ENABLED;
						}
						else
						{
							info.fState = MFS_DISABLED;
						}
						info.wID = item.data.to_menu_id();
						visit(MenuTextConverter{info, temp_string}, item.text);
					}
					else if constexpr(std::is_same_v<Item_t, Submenu>)
					{
						info.fMask |= MIIM_STATE|MIIM_STRING|MIIM_SUBMENU|MIIM_ID;
						info.fType = MFT_STRING;
						if(item.enabled)
						{
							info.fState = MFS_ENABLED;
						}
						else
						{
							info.fState = MFS_DISABLED;
						}
						info.wID = first_menu_id();
						temp_menu.reset(LSDK_CALL_WINAPI_NOTNULL(CreatePopupMenu));
						append(temp_menu, item.items);
						info.hSubMenu = temp_menu.get();
						visit(MenuTextConverter{info, temp_string}, item.name);
					}
				}, v);
				auto const size = LSDK_CALL_WINAPI_NONNEGATIVE(GetMenuItemCount, handle.get());
				LSDK_CALL_WINAPI_NONZERO(InsertMenuItem, handle.get(), size, TRUE, &info);
				temp_menu.release();
			}
		}
		auto generate() const
		-> Handle_t
		{
			Handle_t handle {LSDK_CALL_WINAPI_NOTNULL(CreatePopupMenu)};
			append(handle, items);
			return handle;
		}
	};

	using     ActionMenu = FusionMenu<FusionAceType::    Action>;
	using  ConditionMenu = FusionMenu<FusionAceType:: Condition>;
	using ExpressionMenu = FusionMenu<FusionAceType::Expression>;
}

#endif