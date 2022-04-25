package com.thelogicmaster.test;

import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.ui.ScrollPane;
import com.badlogic.gdx.scenes.scene2d.ui.Skin;
import com.badlogic.gdx.scenes.scene2d.ui.Table;
import com.badlogic.gdx.tests.AbstractTestWrapper;
import com.badlogic.gdx.tests.AccelerometerTest;
import com.badlogic.gdx.tests.ActionSequenceTest;
import com.badlogic.gdx.tests.ActionTest;
import com.badlogic.gdx.tests.AlphaTest;
import com.badlogic.gdx.tests.AnimationTest;
//import com.badlogic.gdx.tests.AnnotationTest;
import com.badlogic.gdx.tests.AssetManagerTest;
import com.badlogic.gdx.tests.AtlasIssueTest;
//import com.badlogic.gdx.tests.BigMeshTest;
import com.badlogic.gdx.tests.BitmapFontAlignmentTest;
import com.badlogic.gdx.tests.BitmapFontFlipTest;
import com.badlogic.gdx.tests.BitmapFontMetricsTest;
import com.badlogic.gdx.tests.BitmapFontTest;
import com.badlogic.gdx.tests.BlitTest;
//import com.badlogic.gdx.tests.Box2DCharacterControllerTest;
//import com.badlogic.gdx.tests.Box2DTest;
//import com.badlogic.gdx.tests.Box2DTestCollection;
import com.badlogic.gdx.tests.BufferUtilsTest;
import com.badlogic.gdx.tests.ClipboardTest;
import com.badlogic.gdx.tests.ColorTest;
import com.badlogic.gdx.tests.ComplexActionTest;
import com.badlogic.gdx.tests.CustomShaderSpriteBatchTest;
import com.badlogic.gdx.tests.DecalTest;
import com.badlogic.gdx.tests.DownloadTest;
import com.badlogic.gdx.tests.EdgeDetectionTest;
import com.badlogic.gdx.tests.FilesTest;
import com.badlogic.gdx.tests.FilterPerformanceTest;
import com.badlogic.gdx.tests.FrameBufferTest;
import com.badlogic.gdx.tests.FramebufferToTextureTest;
import com.badlogic.gdx.tests.GLProfilerErrorTest;
import com.badlogic.gdx.tests.GWTLossyPremultipliedAlphaTest;
import com.badlogic.gdx.tests.GestureDetectorTest;
import com.badlogic.gdx.tests.GroupCullingTest;
import com.badlogic.gdx.tests.GroupFadeTest;
import com.badlogic.gdx.tests.I18NSimpleMessageTest;
import com.badlogic.gdx.tests.ImageScaleTest;
import com.badlogic.gdx.tests.ImageTest;
import com.badlogic.gdx.tests.IndexBufferObjectShaderTest;
import com.badlogic.gdx.tests.IntegerBitmapFontTest;
import com.badlogic.gdx.tests.InterpolationTest;
import com.badlogic.gdx.tests.InverseKinematicsTest;
import com.badlogic.gdx.tests.IsometricTileTest;
//import com.badlogic.gdx.tests.KinematicBodyTest;
import com.badlogic.gdx.tests.LabelScaleTest;
import com.badlogic.gdx.tests.LabelTest;
import com.badlogic.gdx.tests.LifeCycleTest;
import com.badlogic.gdx.tests.MeshShaderTest;
import com.badlogic.gdx.tests.MipMapTest;
import com.badlogic.gdx.tests.MultitouchTest;
import com.badlogic.gdx.tests.MusicTest;
import com.badlogic.gdx.tests.ParallaxTest;
import com.badlogic.gdx.tests.ParticleEmitterTest;
import com.badlogic.gdx.tests.PixelsPerInchTest;
import com.badlogic.gdx.tests.PixmapPackerTest;
import com.badlogic.gdx.tests.PixmapTest;
import com.badlogic.gdx.tests.PreferencesTest;
import com.badlogic.gdx.tests.ProjectiveTextureTest;
import com.badlogic.gdx.tests.QuadTreeFloatNearestTest;
import com.badlogic.gdx.tests.QuadTreeFloatNearestTest;
import com.badlogic.gdx.tests.QuadTreeFloatTest;
import com.badlogic.gdx.tests.ReflectionCorrectnessTest;
//import com.badlogic.gdx.tests.ReflectionTest;
import com.badlogic.gdx.tests.RotationTest;
import com.badlogic.gdx.tests.Scene2dTest;
import com.badlogic.gdx.tests.ShapeRendererTest;
import com.badlogic.gdx.tests.SimpleAnimationTest;
import com.badlogic.gdx.tests.SimpleDecalTest;
import com.badlogic.gdx.tests.SimpleStageCullingTest;
import com.badlogic.gdx.tests.SortedSpriteTest;
import com.badlogic.gdx.tests.SoundTest;
import com.badlogic.gdx.tests.SpriteBatchShaderTest;
import com.badlogic.gdx.tests.SpriteCacheOffsetTest;
import com.badlogic.gdx.tests.SpriteCacheTest;
import com.badlogic.gdx.tests.StageTest;
import com.badlogic.gdx.tests.TableTest;
import com.badlogic.gdx.tests.TextAreaTest;
import com.badlogic.gdx.tests.TextAreaTest2;
import com.badlogic.gdx.tests.TextAreaTest3;
import com.badlogic.gdx.tests.TextButtonTest;
import com.badlogic.gdx.tests.TextureAtlasTest;
import com.badlogic.gdx.tests.TiledMapAtlasAssetManagerTest;
import com.badlogic.gdx.tests.TiledMapObjectLoadingTest;
import com.badlogic.gdx.tests.TimeUtilsTest;
import com.badlogic.gdx.tests.UITest;
import com.badlogic.gdx.tests.VertexBufferObjectShaderTest;
import com.badlogic.gdx.tests.YDownTest;
import com.badlogic.gdx.tests.conformance.DisplayModeTest;
import com.badlogic.gdx.tests.g3d.ModelCacheTest;
import com.badlogic.gdx.tests.g3d.ShadowMappingTest;
import com.badlogic.gdx.tests.gwt.GwtInputTest;
import com.badlogic.gdx.tests.gwt.GwtWindowModeTest;
//import com.badlogic.gdx.tests.math.OctreeTest;
import com.badlogic.gdx.tests.net.OpenBrowserExample;
import com.badlogic.gdx.tests.superkoalio.SuperKoalio;
import com.badlogic.gdx.tests.utils.GdxTest;
import com.badlogic.gdx.utils.reflect.ClassReflection;
import com.badlogic.gdx.utils.reflect.Field;

public class SwitchTestWrapper extends AbstractTestWrapper {

	@Override
	public void create () {
		super.create();

		try {
			Field tableField = ClassReflection.getDeclaredField(AbstractTestWrapper.class, "container");
			Table container = (Table)tableField.get(this);
			ScrollPane scrollPane = (ScrollPane)container.getChild(0);
			Field skinField = ClassReflection.getDeclaredField(AbstractTestWrapper.class, "skin");
			Skin skin = (Skin) skinField.get(this);

			scrollPane.setStyle(skin.get(ScrollPane.ScrollPaneStyle.class));
			scrollPane.setFlickScroll(false);
			scrollPane.setScrollBarPositions(false, true);
			scrollPane.setFadeScrollBars(false);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	protected Instancer[] getTestList () {
		return new Instancer[] {new SwitchInstancer() {
			public GdxTest instance () {
				return new AccelerometerTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ActionTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ActionSequenceTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new AlphaTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new AnimationTest();
			}
//		}, new SwitchInstancer() {
//			public GdxTest instance () {
//				return new AnnotationTest();
//			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new AssetManagerTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new AtlasIssueTest();
			}
//		}, new SwitchInstancer() {
//			public GdxTest instance () {
//				return new BigMeshTest();
//			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new BitmapFontAlignmentTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new BitmapFontFlipTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new BitmapFontTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new BitmapFontMetricsTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new BlitTest();
			}
//		}, new SwitchInstancer() {
//			public GdxTest instance () {
//				return new Box2DCharacterControllerTest();
//			}
//		}, new SwitchInstancer() {
//			public GdxTest instance () {
//				return new Box2DTest();
//			}
//		}, new SwitchInstancer() {
//			public GdxTest instance () {
//				return new Box2DTestCollection();
//			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new BufferUtilsTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ClipboardTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ColorTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ComplexActionTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new CustomShaderSpriteBatchTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new DecalTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new DisplayModeTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new LabelScaleTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new EdgeDetectionTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new FilesTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new FilterPerformanceTest();
			}
		},
			// new SwitchInstancer() {public GdxTest instance(){return new FlickScrollPaneTest();}}, // FIXME this messes up stuff, why?
			new SwitchInstancer() {
				public GdxTest instance () {
					return new FrameBufferTest();
				}
			}, new SwitchInstancer() {
			public GdxTest instance () {
				return new DownloadTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new FramebufferToTextureTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new GestureDetectorTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new GLProfilerErrorTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new GroupCullingTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new GroupFadeTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new GwtInputTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new GwtWindowModeTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new I18NSimpleMessageTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ImageScaleTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ImageTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new IndexBufferObjectShaderTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new IntegerBitmapFontTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new InterpolationTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new InverseKinematicsTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new IsometricTileTest();
			}
//		}, new SwitchInstancer() {
//			public GdxTest instance () {
//				return new KinematicBodyTest();
//			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new LifeCycleTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new LabelTest();
			}
		},
			// new SwitchInstancer() {public GdxTest instance(){return new MatrixJNITest();}}, // No purpose
			new SwitchInstancer() {
				public GdxTest instance () {
					return new MeshShaderTest();
				}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new MipMapTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ModelCacheTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new MultitouchTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new MusicTest();
			}
//		}, new SwitchInstancer() {
//			public GdxTest instance () {
//				return new OctreeTest();
//			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new OpenBrowserExample();
			}
			// }, new SwitchInstancer() { public GdxTest instance () { return new NoncontinuousRenderingTest(); } // FIXME doesn't compile due to
			// the use of Thread
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ParallaxTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ParticleEmitterTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new PixelsPerInchTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new PixmapPackerTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new PixmapTest();
			}
		},
			// new SwitchInstancer() {public GdxTest instance(){return new PixmapBlendingTest();}}, // FIXME no idea why this doesn't
			// work
			new SwitchInstancer() {
				public GdxTest instance () {
					return new PreferencesTest();
				}
			}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ProjectiveTextureTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new RotationTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ReflectionCorrectnessTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new Scene2dTest();
			}

			// new SwitchInstancer() {public GdxTest instance(){return new RunnablePostTest();}}, // Goes into infinite loop
			// new SwitchInstancer() {public GdxTest instance(){return new ScrollPaneTest();}}, // FIXME this messes up stuff, why?
			// new SwitchInstancer() {public GdxTest instance(){return new ShaderMultitextureTest();}}, // FIXME fucks up stuff
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ShadowMappingTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ShapeRendererTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new SimpleAnimationTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new SimpleDecalTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new SimpleStageCullingTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new SortedSpriteTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new SpriteBatchShaderTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new SpriteCacheOffsetTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new SpriteCacheTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new SoundTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new StageTest();
			}
		},
			// new SwitchInstancer() {public GdxTest instance(){return new StagePerformanceTest();}}, // FIXME borks out
			new SwitchInstancer() {
				public GdxTest instance () {
					return new TableTest();
				}
			}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TextButtonTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TextureAtlasTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TiledMapObjectLoadingTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new UITest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new VertexBufferObjectShaderTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new YDownTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new SuperKoalio();
			}
//		}, new SwitchInstancer() {
//			public GdxTest instance () {
//				return new ReflectionTest();
//			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TiledMapAtlasAssetManagerTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TimeUtilsTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new GWTLossyPremultipliedAlphaTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new QuadTreeFloatTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new QuadTreeFloatNearestTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TextAreaTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TextAreaTest2();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TextAreaTest3();
			}
		}};
	}

	private abstract static class SwitchInstancer implements Instancer {
		@Override
		public String getSimpleName () {
			return instance().getClass().getSimpleName();
		}
	}
}
