
--CollisionActors
collisionActor0 = 0;
collisionActor1 = 0;
collisionActor2 = 0;


--Cameras
camera0_16_Camera = 0;


--Texts
PCScore_24_Text = 0;
PlayerScore_25_Text = 0;

--Sounds
BallHitPaddle_26_Sound = 0;
BallHitWall_27_Sound = 0;

--TileMaps

--Sprites
Map_19_Sprite = 0;
PCPaddle_22_Sprite = 0;
Ball_20_Sprite = 0;
PlayerPaddle_21_Sprite = 0;

--ParticleSystems

--ViewPorts
Viewport0_Viewport = 0;

--Layers
layer0_Layer = 0;
layer1_Layer = 0;
layer2_Layer = 0;

--Levels
level0_Level = 0;

function AddCollisionActors0()

	collisionActor0 = CollisionActor();


	---- Adding New Animation 0 ----
	collisionAnimation =  CollisionAnimation();


	-------- New Frame 0 --------
	collisionFrame = CollisionFrame();

	collisionFrame:SetBoundingRectangle(FunRect(512,-512,512,-512)); 
	collisionAnimation:AddCollisionFrame(collisionFrame);


	collisionActor0:AddCollisionAnimation(collisionAnimation);

	-- Adding CollisionActor to Game --
	Game.Get():AddCollisionAssets(collisionActor0);
end

function AddCollisionActors1()

	collisionActor1 = CollisionActor();


	---- Adding New Animation 0 ----
	collisionAnimation =  CollisionAnimation();


	-------- New Frame 0 --------
	collisionFrame = CollisionFrame();

	collisionFrame:SetBoundingRectangle(FunRect(128,-32,32,-128)); 
	collisionFrame:AddCollisionData(Point2D(-22.0,78.0),Point2D(22.0,78.0),0,true);
	collisionFrame:AddCollisionData(Point2D(-22.0,-78.0),Point2D(-22.0,78.0),0,true);
	collisionFrame:AddCollisionData(Point2D(22.0,-78.0),Point2D(-22.0,-78.0),0,true);
	collisionFrame:AddCollisionData(Point2D(22.0,78.0),Point2D(22.0,-78.0),0,true);
	collisionAnimation:AddCollisionFrame(collisionFrame);


	collisionActor1:AddCollisionAnimation(collisionAnimation);

	-- Adding CollisionActor to Game --
	Game.Get():AddCollisionAssets(collisionActor1);
end

function AddCollisionActors2()

	collisionActor2 = CollisionActor();


	---- Adding New Animation 0 ----
	collisionAnimation =  CollisionAnimation();


	-------- New Frame 0 --------
	collisionFrame = CollisionFrame();

	collisionFrame:SetBoundingRectangle(FunRect(32,-32,32,-32)); 
	collisionFrame:AddCollisionData(Point2D(0,0),22,0,true);
	collisionAnimation:AddCollisionFrame(collisionFrame);


	collisionActor2:AddCollisionAnimation(collisionAnimation);

	-- Adding CollisionActor to Game --
	Game.Get():AddCollisionAssets(collisionActor2);
end

function AddCollisionActors()
	AddCollisionActors0()
	AddCollisionActors1()
	AddCollisionActors2()
end

-------------------------LEVEL0--------------------------

--Physics Joints
function MountObjectsLevel0()
end

--static collision
function Level0_Layer0_StaticCollision()
	layer0_Layer:ReadInformation_StaticCollision(Game.Get():GetDirectory().."\\Resources\\Layers Collisions\\level0_layer0.txt" )
end

function Level0_Layer1_StaticCollision()
	layer1_Layer:ReadInformation_StaticCollision(Game.Get():GetDirectory().."\\Resources\\Layers Collisions\\level0_layer1.txt" )
end

function Level0_Layer2_StaticCollision()
	layer2_Layer:ReadInformation_StaticCollision(Game.Get():GetDirectory().."\\Resources\\Layers Collisions\\level0_layer2.txt" )
end



function Set_Level0_Layer0_Objects()

	--TileMaps Setters

	--Texts Setters

	--Sounds Setters

	--Sprites Setters

	--ParticleSystems Setters

	--Joints Setters

	--setStaticCollision
	Level0_Layer0_StaticCollision()
end



function Set_Level0_Layer1_Objects()

	--TileMaps Setters

	--Texts Setters
	PCScore_24_Text= Text("0",Game.Get():GetDirectory().."\\Resources\\Fonts\\DefaultFont\\DefaultFont");
	PCScore_24_Text:SetName("PCScore");
	PCScore_24_Text:SetPosition(Point2D(240.0,280.0));
	PCScore_24_Text:SetLifeTime(0.0);
	PCScore_24_Text:SetVisible(true);
	PCScore_24_Text:SetRotationAngle(0.0);
	PCScore_24_Text:SetScale(1.5,1.5);
	PCScore_24_Text:SetCenter(Point2D(0.0,0.0));
	PCScore_24_Text:SetOpacity(1.0);
	PCScore_24_Text:SetZOrder(1.0);
	layer1_Layer:AddGameObject(PCScore_24_Text)

	PlayerScore_25_Text= Text("0",Game.Get():GetDirectory().."\\Resources\\Fonts\\DefaultFont\\DefaultFont");
	PlayerScore_25_Text:SetName("PlayerScore");
	PlayerScore_25_Text:SetPosition(Point2D(-240.0,280.0));
	PlayerScore_25_Text:SetLifeTime(0.0);
	PlayerScore_25_Text:SetVisible(true);
	PlayerScore_25_Text:SetRotationAngle(0.0);
	PlayerScore_25_Text:SetScale(1.5,1.5);
	PlayerScore_25_Text:SetCenter(Point2D(0.0,0.0));
	PlayerScore_25_Text:SetOpacity(1.0);
	PlayerScore_25_Text:SetZOrder(1.0);
	layer1_Layer:AddGameObject(PlayerScore_25_Text)



	--Sounds Setters
	sound_File = Game.Get():GetDirectory().."\\Resources\\Sounds\\BallHitPaddle.wav";
	BallHitPaddle_26_Sound = Sound(sound_File,SoundSpatialization.SoundSpatializationNone,10.0,false,0.0);
	BallHitPaddle_26_Sound:SetName("BallHitPaddle");
	BallHitPaddle_26_Sound:SetPosition(Point2D(0.0,0.0));
	BallHitPaddle_26_Sound:SetVolume(0.49);
	BallHitPaddle_26_Sound:SetPitch(1.0);
	BallHitPaddle_26_Sound:SetLifeTime(0.0);
	layer1_Layer:AddGameObject(BallHitPaddle_26_Sound)

	sound_File = Game.Get():GetDirectory().."\\Resources\\Sounds\\BallHitWall.wav";
	BallHitWall_27_Sound = Sound(sound_File,SoundSpatialization.SoundSpatializationNone,10.0,false,0.0);
	BallHitWall_27_Sound:SetName("BallHitWall");
	BallHitWall_27_Sound:SetPosition(Point2D(0.0,0.0));
	BallHitWall_27_Sound:SetVolume(0.51);
	BallHitWall_27_Sound:SetPitch(1.0);
	BallHitWall_27_Sound:SetLifeTime(0.0);
	layer1_Layer:AddGameObject(BallHitWall_27_Sound)



	--Sprites Setters
	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\Map.png",1,1,1.0);
	anim0:SetName("Map");
	Map_19_Sprite = Sprite(anim0);

	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		dynamicCollisionData =  DynamicObject();
		dynamicCollisionData:AddCollisionData(collisionActor0);
		dynamicCollisionData:SetCollisionType(false);
		dynamicCollisionData:SetCollisionThickness(0.0);
		dynamicCollisionData:SetBoundingRectangleCheckingTileMap(true);
		dynamicCollisionData:SetZCollision(0);
		dynamicCollisionData:SetCanCollid(0,true);
		dynamicCollisionData:SetUpdateOnIdle(false);
		Map_19_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	Map_19_Sprite:SetName("Map");
	Map_19_Sprite:SetCollisionActorIndex(0);
	Map_19_Sprite:SetOpacity(1.0);
	Map_19_Sprite:Play(true);
	Map_19_Sprite:SetPosition(Point2D(0.0,0.0));
	Map_19_Sprite:SetCurrentAnimationIndex(0);
	Map_19_Sprite:SetCurrentFrameIndex(0);
	Map_19_Sprite:SetLoop(true);
	Map_19_Sprite:SetAnimationSpeed(1.0);
	Map_19_Sprite:SetFlipHorizontal(false);
	Map_19_Sprite:SetFlipVertical(false);
	Map_19_Sprite:SetLifeTime(0.0);
	Map_19_Sprite:SetVisible(true);
	Map_19_Sprite:SetRotationAngle(0.0);
	Map_19_Sprite:SetScale(1.0, 1.0);
	Map_19_Sprite:SetCenter(Point2D(0.0,0.0));
	Map_19_Sprite:SetZOrder(0.0);
	
	layer1_Layer:AddGameObject(Map_19_Sprite)

	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\Paddle.png",1,1,1.0);
	anim0:SetName("Paddle");
	PCPaddle_22_Sprite = PCBehavior(anim0);

	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		dynamicCollisionData =  DynamicObject();
		dynamicCollisionData:AddCollisionData(collisionActor1);
		dynamicCollisionData:SetCollisionType(true);
		dynamicCollisionData:SetCollisionThickness(2.0);
		dynamicCollisionData:SetBoundingRectangleCheckingTileMap(true);
		dynamicCollisionData:SetZCollision(0);
		dynamicCollisionData:SetCanCollid(0,true);
		dynamicCollisionData:SetCanCollid(1,true);
		dynamicCollisionData:SetUpdateOnIdle(false);
		PCPaddle_22_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	PCPaddle_22_Sprite:SetName("PCPaddle");
	PCPaddle_22_Sprite:SetCollisionActorIndex(1);
	PCPaddle_22_Sprite:SetOpacity(1.0);
	PCPaddle_22_Sprite:Play(true);
	PCPaddle_22_Sprite:SetPosition(Point2D(365.0,0.0));
	PCPaddle_22_Sprite:SetCurrentAnimationIndex(0);
	PCPaddle_22_Sprite:SetCurrentFrameIndex(0);
	PCPaddle_22_Sprite:SetLoop(true);
	PCPaddle_22_Sprite:SetAnimationSpeed(1.0);
	PCPaddle_22_Sprite:SetFlipHorizontal(false);
	PCPaddle_22_Sprite:SetFlipVertical(false);
	PCPaddle_22_Sprite:SetLifeTime(0.0);
	PCPaddle_22_Sprite:SetVisible(true);
	PCPaddle_22_Sprite:SetRotationAngle(0.0);
	PCPaddle_22_Sprite:SetScale(1.0, 1.0);
	PCPaddle_22_Sprite:SetCenter(Point2D(0.0,0.0));
	PCPaddle_22_Sprite:SetZOrder(1.0);
	
	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		PCPaddle_22_Sprite:SetCenter(Point2D(0.0,0.0));
		PCPaddle_22_Sprite:AddPhysicalProperties(MassProperties(0.0,0.0,Point2D(0.0,0.0)),Physics.ODESolverMethodEuler);
		PCPaddle_22_Sprite:SetVelocity(Vector2D(0.0,0.0));
		PCPaddle_22_Sprite:SetAngularVelocity(0.0);
	end

	layer1_Layer:AddGameObject(PCPaddle_22_Sprite)

	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\Ball.png",1,1,1.0);
	anim0:SetName("Ball");
	Ball_20_Sprite = BallBehavior(anim0);

	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		dynamicCollisionData =  DynamicObject();
		dynamicCollisionData:AddCollisionData(collisionActor2);
		dynamicCollisionData:SetCollisionType(true);
		dynamicCollisionData:SetCollisionThickness(2.0);
		dynamicCollisionData:SetBoundingRectangleCheckingTileMap(true);
		dynamicCollisionData:SetZCollision(1);
		dynamicCollisionData:SetCanCollid(0,true);
		dynamicCollisionData:SetUpdateOnIdle(false);
		Ball_20_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	Ball_20_Sprite:SetName("Ball");
	Ball_20_Sprite:SetCollisionActorIndex(2);
	Ball_20_Sprite:SetOpacity(1.0);
	Ball_20_Sprite:Play(true);
	Ball_20_Sprite:SetPosition(Point2D(0.0,0.0));
	Ball_20_Sprite:SetCurrentAnimationIndex(0);
	Ball_20_Sprite:SetCurrentFrameIndex(0);
	Ball_20_Sprite:SetLoop(true);
	Ball_20_Sprite:SetAnimationSpeed(1.0);
	Ball_20_Sprite:SetFlipHorizontal(false);
	Ball_20_Sprite:SetFlipVertical(false);
	Ball_20_Sprite:SetLifeTime(0.0);
	Ball_20_Sprite:SetVisible(true);
	Ball_20_Sprite:SetRotationAngle(0.0);
	Ball_20_Sprite:SetScale(1.0, 1.0);
	Ball_20_Sprite:SetCenter(Point2D(0.0,0.0));
	Ball_20_Sprite:SetZOrder(1.0);
	
	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		Ball_20_Sprite:SetCenter(Point2D(0.0,0.0));
		Ball_20_Sprite:AddPhysicalProperties(MassProperties(0.03,1.0,Point2D(0.0,0.0)),Physics.ODESolverMethodEuler);
		Ball_20_Sprite:SetVelocity(Vector2D(0.0,0.0));
		Ball_20_Sprite:SetAngularVelocity(0.0);
	end

	layer1_Layer:AddGameObject(Ball_20_Sprite)

	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\Paddle.png",1,1,1.0);
	anim0:SetName("Paddle");
	PlayerPaddle_21_Sprite = PlayerBehavior(anim0);

	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		dynamicCollisionData =  DynamicObject();
		dynamicCollisionData:AddCollisionData(collisionActor1);
		dynamicCollisionData:SetCollisionType(true);
		dynamicCollisionData:SetCollisionThickness(2.0);
		dynamicCollisionData:SetBoundingRectangleCheckingTileMap(true);
		dynamicCollisionData:SetZCollision(0);
		dynamicCollisionData:SetCanCollid(0,true);
		dynamicCollisionData:SetCanCollid(1,true);
		dynamicCollisionData:SetUpdateOnIdle(false);
		PlayerPaddle_21_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	PlayerPaddle_21_Sprite:SetName("PlayerPaddle");
	PlayerPaddle_21_Sprite:SetCollisionActorIndex(1);
	PlayerPaddle_21_Sprite:SetOpacity(1.0);
	PlayerPaddle_21_Sprite:Play(true);
	PlayerPaddle_21_Sprite:SetPosition(Point2D(-365.0,0.0));
	PlayerPaddle_21_Sprite:SetCurrentAnimationIndex(0);
	PlayerPaddle_21_Sprite:SetCurrentFrameIndex(0);
	PlayerPaddle_21_Sprite:SetLoop(true);
	PlayerPaddle_21_Sprite:SetAnimationSpeed(1.0);
	PlayerPaddle_21_Sprite:SetFlipHorizontal(false);
	PlayerPaddle_21_Sprite:SetFlipVertical(false);
	PlayerPaddle_21_Sprite:SetLifeTime(0.0);
	PlayerPaddle_21_Sprite:SetVisible(true);
	PlayerPaddle_21_Sprite:SetRotationAngle(0.0);
	PlayerPaddle_21_Sprite:SetScale(1.0, 1.0);
	PlayerPaddle_21_Sprite:SetCenter(Point2D(0.0,0.0));
	PlayerPaddle_21_Sprite:SetZOrder(1.0);
	
	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		PlayerPaddle_21_Sprite:SetCenter(Point2D(0.0,0.0));
		PlayerPaddle_21_Sprite:AddPhysicalProperties(MassProperties(0.0,0.0,Point2D(0.0,0.0)),Physics.ODESolverMethodEuler);
		PlayerPaddle_21_Sprite:SetVelocity(Vector2D(0.0,0.0));
		PlayerPaddle_21_Sprite:SetAngularVelocity(0.0);
	end

	layer1_Layer:AddGameObject(PlayerPaddle_21_Sprite)



	--ParticleSystems Setters

	--Joints Setters

	--setStaticCollision
	Level0_Layer1_StaticCollision()
end




function Set_Level0_Layer2_Objects()

	--TileMaps Setters

	--Texts Setters

	--Sounds Setters

	--Sprites Setters

	--ParticleSystems Setters

	--Joints Setters

	--setStaticCollision
	Level0_Layer2_StaticCollision()
end

function CreateLevel0()
	level0_Level = Level();
	level0_Level:SetName("level0");
	level0_Level:SetClearBackBuffer(false);

	CreateJukeBox0();
	level0_Level:CreateJukeBox(JukeBox0);
	layer0_Layer = Layer(0.0);
	layer0_Layer:SetName("level0_HUD");

	layer0_Layer:SetCollisionProperties(Point2D(-400,-300),800,600);
	layer1_Layer = Layer(0.0);
	layer1_Layer:SetName("layer1");
	layer1_Layer:SetScale(1.0,1.0);
	layer1_Layer:SetRotation(0.0);
	layer1_Layer:SetCollisionProperties(Point2D(-512,-512),1024,1024);

	layer2_Layer = Layer(724.2641);
	layer2_Layer:SetName("layer2");
	layer2_Layer:SetScale(1.0,1.0);
	layer2_Layer:SetRotation(0.0);
	layer2_Layer:SetCollisionProperties(Point2D(-400,-300),800,600);


	camera0_16_Camera = Camera(45.0);
	camera0_16_Camera:SetName("camera0");
	camera0_16_Camera:SetPosition(Point2D(0.0,0.0));
	layer2_Layer:AddGameObject(camera0_16_Camera);


	Viewport0_Viewport = Viewport(0, 0, 800, 600);
	Viewport0_Viewport:SetClearColor(Color(0.2509804 ,0.2509804 ,0.2509804));
	Viewport0_Viewport:SetCamera(camera0_16_Camera);

	level0_Level:AddLayer(layer0_Layer);
	level0_Level:AddLayer(layer1_Layer);
	level0_Level:AddLayer(layer2_Layer);

	level0_Level:AddViewport(Viewport0_Viewport);

	Set_Level0_Layer0_Objects();
	Set_Level0_Layer1_Objects();
	Set_Level0_Layer2_Objects();

	MountObjectsLevel0();
	CreateLevelForms(0);
	return level0_Level;
end


function GetLevelsCount()
	 return 1;
end

function  CreateJukeBox0()
 
	--JukeBox0
	music_File_0_JukeBox0 = Game.Get():GetDirectory().."\\Resources\\JukeBoxes\\JukeBox0\\LevelMusic.wav";

	JukeBox0 =  JukeBox(music_File_0_JukeBox0);
	JukeBox0:SetFadeTime(0.0);
	Random.SetSeed(Time.GetTime());
	JukeBox0:SetShuffle(false);
	JukeBox0:SetRepeat(true);
	JukeBox0:PlayMusic();
	JukeBox0:SetMusicVolume(0.5);

end

function CreateLevelForms(index)

	if (index ==0)
	then

		end

end

function CreateLevel(index)
	--Assets
	AddCollisionActors();

	if (index ==0)
	then
		return CreateLevel0();
		end

	return 0;
end

function GetLevelIndexFromName(levelName)
	if(levelName == "level0")
	then
		return 0;
	else	end
	return -1;
end

function Reset()

	--Cameras
	camera0_16_Camera = 0;

	--Texts
	PCScore_24_Text = 0;
	PlayerScore_25_Text = 0;

	--Sounds
	BallHitPaddle_26_Sound = 0;
	BallHitWall_27_Sound = 0;

	--TileMaps

	--Sprites
	Map_19_Sprite = 0;
	PCPaddle_22_Sprite = 0;
	Ball_20_Sprite = 0;
	PlayerPaddle_21_Sprite = 0;

	--ParticleSystems

	--ViewPorts
	Viewport0_Viewport = 0;

	--Layers
	layer0_Layer = 0;
	layer1_Layer = 0;
	layer2_Layer = 0;

	--Levels
	level0_Level = 0;

end
function MountObjectsLevel0()
	
end
