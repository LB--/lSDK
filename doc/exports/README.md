Here you will find documentation for all functions that are exported by the module definition file (.def) for your project.
Functions documented in the `general` directory must be exported in all build configurations.
Functions documented in the `edittime` and `runtime/debugger` directory need only be exported in edittime configurations - these will be used when the user is creating their project inside Fusion.
Functions documented in the `runtime` directory (but not the `runtime/debugger` directory) must be exported in call build configurations, both edittime and runtime, as Fusion will use the edittime MFX for the runtime that is executed from the editor interface.
The runtime only configurations are used for the final export of the user's project, and don't need any editor or debugger functionality.

Typically this means you just need two module definition files - one for edittime, and one for runtime-only.
See the example project for an example of this.

As explained in `minimum-required.md`, a vast majority of functions are completely optional.
You only need to implement and export a function if you need to customize its behavior.
For example, if you don't have any expressions, you don't need to export any functions relating to expressions. Some functions require a fallback in the resources file of your project if you don't export them, so keep an eye out for that.
