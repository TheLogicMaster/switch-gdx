package com.thelogicmaster.test;

import com.badlogic.gdx.scenes.scene2d.ui.ScrollPane;
import com.badlogic.gdx.scenes.scene2d.ui.Skin;
import com.badlogic.gdx.scenes.scene2d.ui.Table;
import com.badlogic.gdx.tests.extensions.FreeTypeAtlasTest;
import com.badlogic.gdx.tests.extensions.FreeTypeDisposeTest;
import com.badlogic.gdx.tests.extensions.FreeTypeFontLoaderTest;
import com.badlogic.gdx.tests.extensions.FreeTypeIncrementalTest;
import com.badlogic.gdx.tests.extensions.FreeTypeMetricsTest;
import com.badlogic.gdx.tests.extensions.FreeTypePackTest;
import com.badlogic.gdx.tests.extensions.FreeTypeTest;
import com.badlogic.gdx.tests.extensions.InternationalFontsTest;
import com.badlogic.gdx.utils.reflect.ClassReflection;
import com.badlogic.gdx.utils.reflect.Field;
import com.badlogic.gdx.tests.*;
import com.badlogic.gdx.tests.QuadTreeFloatNearestTest;
import com.badlogic.gdx.tests.ReflectionTest;
import com.badlogic.gdx.tests.bench.TiledMapBench;
import com.badlogic.gdx.tests.conformance.DisplayModeTest;
import com.badlogic.gdx.tests.examples.MoveSpriteExample;
import com.badlogic.gdx.tests.g2d.ProgressiveJPEGTest;
import com.badlogic.gdx.tests.g3d.Animation3DTest;
import com.badlogic.gdx.tests.g3d.AnisotropyTest;
import com.badlogic.gdx.tests.g3d.Basic3DSceneTest;
import com.badlogic.gdx.tests.g3d.Basic3DTest;
import com.badlogic.gdx.tests.g3d.Benchmark3DTest;
import com.badlogic.gdx.tests.g3d.FogTest;
import com.badlogic.gdx.tests.g3d.FrameBufferCubemapTest;
import com.badlogic.gdx.tests.g3d.HeightMapTest;
import com.badlogic.gdx.tests.g3d.LightsTest;
import com.badlogic.gdx.tests.g3d.MaterialEmissiveTest;
import com.badlogic.gdx.tests.g3d.MaterialTest;
import com.badlogic.gdx.tests.g3d.MeshBuilderTest;
import com.badlogic.gdx.tests.g3d.ModelCacheTest;
import com.badlogic.gdx.tests.g3d.ModelLoaderTest;
import com.badlogic.gdx.tests.g3d.ModelTest;
import com.badlogic.gdx.tests.g3d.MultipleRenderTargetTest;
import com.badlogic.gdx.tests.g3d.ParticleControllerInfluencerSingleTest;
import com.badlogic.gdx.tests.g3d.ParticleControllerTest;
import com.badlogic.gdx.tests.g3d.PolarAccelerationTest;
import com.badlogic.gdx.tests.g3d.ShaderCollectionTest;
import com.badlogic.gdx.tests.g3d.ShaderTest;
import com.badlogic.gdx.tests.g3d.ShadowMappingTest;
import com.badlogic.gdx.tests.g3d.SkeletonTest;
import com.badlogic.gdx.tests.g3d.TangentialAccelerationTest;
import com.badlogic.gdx.tests.g3d.TextureArrayTest;
import com.badlogic.gdx.tests.g3d.TextureRegion3DTest;
import com.badlogic.gdx.tests.g3d.utils.DefaultTextureBinderTest;
import com.badlogic.gdx.tests.g3d.voxel.VoxelTest;
import com.badlogic.gdx.tests.gles2.HelloTriangle;
import com.badlogic.gdx.tests.gles2.MipMap2D;
import com.badlogic.gdx.tests.gles2.SimpleVertexShader;
import com.badlogic.gdx.tests.gles3.InstancedRenderingTest;
import com.badlogic.gdx.tests.gles3.PixelBufferObjectTest;
import com.badlogic.gdx.tests.gwt.GwtInputTest;
import com.badlogic.gdx.tests.net.HttpRequestExample;
import com.badlogic.gdx.tests.net.NetAPITest;
import com.badlogic.gdx.tests.net.OpenBrowserExample;
import com.badlogic.gdx.tests.net.PingPongSocketExample;
import com.badlogic.gdx.tests.superkoalio.SuperKoalio;
import com.badlogic.gdx.tests.utils.GdxTest;
import com.badlogic.gdx.tests.utils.IssueTest;
import com.badlogic.gdx.tests.AnnotationTest;
import com.badlogic.gdx.tests.Box2DCharacterControllerTest;
import com.badlogic.gdx.tests.Box2DTest;
import com.badlogic.gdx.tests.Box2DTestCollection;
import com.badlogic.gdx.tests.KinematicBodyTest;

public class SwitchTestWrapper extends AbstractTestWrapper {

	@Override
	public void create () {
		super.create();

		try {
			Field tableField = ClassReflection.getDeclaredField(AbstractTestWrapper.class, "container");
			Table container = (Table)tableField.get(this);
			ScrollPane scrollPane = (ScrollPane)container.getChild(0);
			Field skinField = ClassReflection.getDeclaredField(AbstractTestWrapper.class, "skin");
			Skin skin = (Skin)skinField.get(this);

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
			@Override
			public GdxTest instance () {
				return new SwitchControllerTest();
			}
		}, new SwitchInstancer() {
			@Override
			public GdxTest instance () {
				return new SwitchInputTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new JniGenTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new SwitchSocketTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ThreadTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new AccelerometerTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TiledMapBench();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new MoveSpriteExample();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new DefaultTextureBinderTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ProgressiveJPEGTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new VoxelTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new Animation3DTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new AnisotropyTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new Basic3DSceneTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new Basic3DTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new Benchmark3DTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new FogTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new FrameBufferCubemapTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new HeightMapTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new LightsTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new MaterialEmissiveTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new MaterialTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new MeshBuilderTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ModelLoaderTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ModelTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new MultipleRenderTargetTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ParticleControllerInfluencerSingleTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ParticleControllerTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new PolarAccelerationTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ShaderCollectionTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ShaderTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new SkeletonTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TangentialAccelerationTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TextureArrayTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TextureRegion3DTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new HelloTriangle();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new MipMap2D();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new SimpleVertexShader();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new InstancedRenderingTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new PixelBufferObjectTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new HttpRequestExample();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new NetAPITest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new PingPongSocketExample();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new IssueTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new Affine2Test();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new AudioDeviceTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new AudioRecorderTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new BitmapFontAtlasRegionTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new BitmapFontDistanceFieldTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new Bresenham2Test();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new CollectionsTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ContainerTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new CoordinatesTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new CpuSpriteBatchTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new CullTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new DelaunayTriangulatorTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new DeltaTimeTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new DpiTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new DragAndDropTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ETC1Test();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ExitTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ExternalMusicTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new FloatTextureTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new GLES30Test();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new GroupTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new HexagonalTiledMapTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new I18NMessageTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new IntersectorOverlapConvexPolygonsTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new JsonTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new KTXTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new NinePatchTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ParticleEmitterChangeSpriteTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ParticleEmittersTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new PathTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new PixelPerfectTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new PixmapPackerIOTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new PngTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new PolygonRegionTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new PolygonSpriteTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ProjectTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new RunnablePostTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ScrollPane2Test();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ScrollPaneScrollBarsTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ScrollPaneTextAreaTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ScrollPaneWithDynamicScrolling();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new SelectTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new SensorTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ShapeRendererAlphaTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ShortSoundTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new SpriteBatchOriginScaleTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new SpriteBatchRotationTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new StageDebugTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TableLayoutTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TextInputDialogTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TextureDataTest();
			}
//		}, new SwitchInstancer() {
//			public GdxTest instance () {
//				return new TextureDownloadTest();
//			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TideMapAssetManagerTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TideMapDirectLoaderTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TiledMapAnimationLoadingTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TiledMapAssetManagerTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TiledMapDirectLoaderTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TiledMapGroupLayerTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TiledMapLayerOffsetTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TiledMapModifiedExternalTilesetTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TileTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TouchpadTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new TreeTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new UBJsonTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new UtfFontTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new VBOWithVAOPerformanceTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new Vector2dTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new VibratorTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ViewportTest1();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ViewportTest2();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ViewportTest3();
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
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new AnnotationTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new AssetManagerTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new AtlasIssueTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new BigMeshTest();
			}
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
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new Box2DCharacterControllerTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new Box2DTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new Box2DTestCollection();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new BufferUtilsTest();
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
		}, new SwitchInstancer() {
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
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new LifeCycleTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new LabelTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new MatrixJNITest();
			}
		}, new SwitchInstancer() {
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
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new OpenBrowserExample();
			}
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
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new PixmapBlendingTest();
			}
		}, new SwitchInstancer() {
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
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ScrollPaneTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ShaderMultitextureTest();
			}
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
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new StagePerformanceTest();
			}
		}, new SwitchInstancer() {
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
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new ReflectionTest();
			}
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
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new FreeTypeAtlasTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new FreeTypeDisposeTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new FreeTypeFontLoaderTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new FreeTypeIncrementalTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new FreeTypeMetricsTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new FreeTypePackTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new FreeTypeTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new InternationalFontsTest();
			}
		}, new SwitchInstancer() {
			public GdxTest instance () {
				return new KinematicBodyTest();
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
