```cpp
#ifdef FUSION_GET_COMPATIBILITY
auto FUSION_API GetInfos(std::int32_t const which) noexcept
-> std::uint32_t
```
This is a required function that Fusion calls to determine compatibility with your extension.

| Value of `which` | Value to return |
| --- | --- |
| `KGI_VERSION` | `FUSION_GET_COMPATIBILITY_VERSION` |
| `KGI_PLUGIN` | `FUSION_GET_COMPATIBILITY_PLUGIN` |
| `KGI_PRODUCT` | One of `PRODUCT_VERSION_HOME` (The Games Factory), `PRODUCT_VERSION_STANDARD` (Fusion), or `PRODUCT_VERSION_DEV` (Fusion Developer) |
| `KGI_BUILD` | The build number of Fusion you are targeting, ideally the latest (e.g. `290`) |
| `KGI_UNICODE` | `FUSION_GET_COMPATIBILITY_UNICODE` (`TRUE` when building for Unicode and `FALSE` for ANSI) |
| `KGI_MULTIPLESUBTYPE` | `FUSION_GET_COMPATIBILITY_MULTIPLE_SUBTYPES` (`TRUE` if your extension supports multiple subtypes, see relevant documentation) |

For any unknown value of `which`, return `0`.
