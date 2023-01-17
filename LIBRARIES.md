# SwitchGDX Library Compatibility
Libraries that don't have native components should work by default, but may require creating entries in the switch.json config
file to enable reflection metadata for needed classes (Any types used by GDX Array, for example). Any library that uses
native code must have bindings for the Clearwing VM written by hand or by inlining the native code jnigen style (See
[Clearwing](https://github.com/TheLogicMaster/clearwing-vm) for details). 

## GDX Box2D
Fully supported

## GDX Freetype
Fully supported

## GDX Controllers
Fully supported and used internally

## [RegExodus](https://github.com/tommyettinger/RegExodus)
Fully supported and used internally for regex

## [TenPatch](https://github.com/raeleus/TenPatch)
Fully supported. Requires the following added to switch.json:
```json
{
  "reflective": [
    "com.ray3k.tenpatch.TenPatchDrawable"
  ]
}
```

## [Colorful GDX](https://github.com/tommyettinger/colorful-gdx)
Fully supported

## [Artemis-ODB](https://github.com/junkdog/artemis-odb)
Fully supported. Requires the following added to switch.json:
```json
{
  "reflective": [
    "com.artemis.BaseSystem",
    "com.artemis.utils.BitVector",
    "com.artemis.utils.Bag",
    "com.artemis.Aspect.Builder",
    "com.artemis.WildBag",
    "com.artemis.EntityEdit",
    "com.artemis.EntityTransmuter.TransmuteOperation",
    "com.artemis.ComponentRemover",
    "com.artemis.ComponentTypeFactory.ComponentTypeListener",
    "com.artemis.EntitySubscription",
    "com.artemis.Component",
    "com.artemis.Aspect",
    "com.artemis.Entity"
  ]
}
```

## [Hyperlap2D](https://github.com/rednblackgames/HyperLap2D)
Fully supported. Requires the following added to switch.json in addition to the Artemis-ODB entries:
```json
{
  "reflective": [
    "games.rednblack.hyperrunner.component.*",
    "games.rednblack.hyperrunner.system.*",
    "games.rednblack.hyperrunner.script.*",
    "games.rednblack.editor.renderer.data.*",
    "games.rednblack.editor.renderer.components.**Component",
    "games.rednblack.editor.renderer.components.normal.NormalMapRendering",
    "games.rednblack.editor.renderer.SceneLoader",
    "games.rednblack.editor.renderer.systems.**System",
    "games.rednblack.editor.renderer.box2dLight.LightData",
    "games.rednblack.editor.renderer.systems.render.HyperLap2dRenderer",
    "games.rednblack.editor.renderer.systems.render.logic.*",
    "games.rednblack.editor.renderer.systems.action.logic.*",
    "games.rednblack.editor.renderer.factory.component.*",
    "games.rednblack.editor.renderer.factory.EntityFactory",
    "java.util.HashSet"
  ]
}
```

## [ScreenManager](https://github.com/crykn/libgdx-screenmanager)
Fully supported

## [ControllerScene2D](https://github.com/MrStahlfelge/gdx-controllerutils/wiki/Button-operable-Scene2d)
Fully supported

## [GDX VFX](https://github.com/crashinvaders/gdx-vfx)
Fully supported

## [Ashley](https://github.com/libgdx/ashley)
Fully supported. Requires the following entry added to switch.json:
```json
{
  "reflective": [
    "com.badlogic.ashley.core.Entity"
  ]
}
```

## [VisUI](https://github.com/kotcrab/vis-ui)
Mostly supported. File chooser stuff won't work and will cause compilation errors if used. Requires
the following switch.json entry:
```json
{
  "reflective": [
    "com.kotcrab.vis.ui.**Style"
  ]
}
```
