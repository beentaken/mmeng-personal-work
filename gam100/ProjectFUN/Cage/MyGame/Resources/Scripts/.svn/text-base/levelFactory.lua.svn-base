
--CollisionActors
collisionActor0 = 0;
collisionActor1 = 0;
collisionActor2 = 0;


--Cameras
camera0_2_Camera = 0;


--Texts

--Sounds
BGM_13_Sound = 0;

--TileMaps

--Sprites
Map_5_Sprite = 0;
Ball0_6_Sprite = 0;
Cage_8_Sprite = 0;
Ball1_11_Sprite = 0;
Ball2_12_Sprite = 0;

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

	collisionFrame:SetBoundingRectangle(FunRect(8,-8,8,-8)); 
	collisionFrame:AddCollisionData(Point2D(0,0),8,0,true);
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

	collisionFrame:SetBoundingRectangle(FunRect(256,-256,256,-256)); 
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

	--Sounds Setters
	sound_File = Game.Get():GetDirectory().."\\Resources\\Sounds\\BG.wav";
	BGM_13_Sound = Sound(sound_File,SoundSpatialization.SoundSpatializationNone,10.0,true,0.0);
	BGM_13_Sound:SetName("BGM");
	BGM_13_Sound:SetPosition(Point2D(0.0,0.0));
	BGM_13_Sound:Play(false);
	BGM_13_Sound:SetVolume(1.0);
	BGM_13_Sound:SetPitch(1.0);
	BGM_13_Sound:SetLifeTime(0.0);
	layer1_Layer:AddGameObject(BGM_13_Sound)



	--Sprites Setters
	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\Map.png",1,1,1.0);
	anim0:SetName("Map");
	Map_5_Sprite = Sprite(anim0);

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
		Map_5_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	Map_5_Sprite:SetName("Map");
	Map_5_Sprite:SetCollisionActorIndex(0);
	Map_5_Sprite:SetOpacity(1.0);
	Map_5_Sprite:Play(true);
	Map_5_Sprite:SetPosition(Point2D(0.0,0.0));
	Map_5_Sprite:SetCurrentAnimationIndex(0);
	Map_5_Sprite:SetCurrentFrameIndex(0);
	Map_5_Sprite:SetLoop(true);
	Map_5_Sprite:SetAnimationSpeed(1.0);
	Map_5_Sprite:SetFlipHorizontal(false);
	Map_5_Sprite:SetFlipVertical(false);
	Map_5_Sprite:SetLifeTime(0.0);
	Map_5_Sprite:SetVisible(true);
	Map_5_Sprite:SetRotationAngle(0.0);
	Map_5_Sprite:SetScale(1.0, 1.0);
	Map_5_Sprite:SetCenter(Point2D(0.0,0.0));
	Map_5_Sprite:SetZOrder(0.0);
	
	layer1_Layer:AddGameObject(Map_5_Sprite)

	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\Ball.png",1,1,1.0);
	anim0:SetName("Ball");
	Ball0_6_Sprite = Sprite(anim0);

	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		dynamicCollisionData =  DynamicObject();
		dynamicCollisionData:AddCollisionData(collisionActor1);
		dynamicCollisionData:SetCollisionType(true);
		dynamicCollisionData:SetCollisionThickness(0.0);
		dynamicCollisionData:SetBoundingRectangleCheckingTileMap(true);
		dynamicCollisionData:SetZCollision(1);
		dynamicCollisionData:SetCanCollid(0,true);
		dynamicCollisionData:SetUpdateOnIdle(false);
		Ball0_6_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	Ball0_6_Sprite:SetName("Ball0");
	Ball0_6_Sprite:SetCollisionActorIndex(1);
	Ball0_6_Sprite:SetOpacity(1.0);
	Ball0_6_Sprite:Play(true);
	Ball0_6_Sprite:SetPosition(Point2D(-300.0,-200.0));
	Ball0_6_Sprite:SetCurrentAnimationIndex(0);
	Ball0_6_Sprite:SetCurrentFrameIndex(0);
	Ball0_6_Sprite:SetLoop(true);
	Ball0_6_Sprite:SetAnimationSpeed(1.0);
	Ball0_6_Sprite:SetFlipHorizontal(false);
	Ball0_6_Sprite:SetFlipVertical(false);
	Ball0_6_Sprite:SetLifeTime(0.0);
	Ball0_6_Sprite:SetVisible(true);
	Ball0_6_Sprite:SetRotationAngle(0.0);
	Ball0_6_Sprite:SetScale(1.0, 1.0);
	Ball0_6_Sprite:SetCenter(Point2D(0.0,0.0));
	Ball0_6_Sprite:SetZOrder(0.0);
	
	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		Ball0_6_Sprite:SetCenter(Point2D(0.0,0.0));
		Ball0_6_Sprite:AddPhysicalProperties(MassProperties(0.01,1.0,Point2D(0.0,0.0)),Physics.ODESolverMethodEuler);
		Ball0_6_Sprite:AddForce(ConstantForce(Vector2D(1.0,1.0),0.2));
		Ball0_6_Sprite:SetVelocity(Vector2D(0.0,0.0));
		Ball0_6_Sprite:SetAngularVelocity(0.0);
	end

	layer1_Layer:AddGameObject(Ball0_6_Sprite)

	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\Cage.png",1,1,1.0);
	anim0:SetName("Cage");
	Cage_8_Sprite = Sprite(anim0);

	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		dynamicCollisionData =  DynamicObject();
		dynamicCollisionData:AddCollisionData(collisionActor2);
		dynamicCollisionData:SetCollisionType(false);
		dynamicCollisionData:SetCollisionThickness(0.0);
		dynamicCollisionData:SetBoundingRectangleCheckingTileMap(true);
		dynamicCollisionData:SetZCollision(0);
		dynamicCollisionData:SetCanCollid(0,true);
		dynamicCollisionData:SetUpdateOnIdle(false);
		Cage_8_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	Cage_8_Sprite:SetName("Cage");
	Cage_8_Sprite:SetCollisionActorIndex(2);
	Cage_8_Sprite:SetOpacity(1.0);
	Cage_8_Sprite:Play(true);
	Cage_8_Sprite:SetPosition(Point2D(0.0,-40.0));
	Cage_8_Sprite:SetCurrentAnimationIndex(0);
	Cage_8_Sprite:SetCurrentFrameIndex(0);
	Cage_8_Sprite:SetLoop(true);
	Cage_8_Sprite:SetAnimationSpeed(1.0);
	Cage_8_Sprite:SetFlipHorizontal(false);
	Cage_8_Sprite:SetFlipVertical(false);
	Cage_8_Sprite:SetLifeTime(0.0);
	Cage_8_Sprite:SetVisible(true);
	Cage_8_Sprite:SetRotationAngle(0.0);
	Cage_8_Sprite:SetScale(1.0, 1.0);
	Cage_8_Sprite:SetCenter(Point2D(0.0,0.0));
	Cage_8_Sprite:SetZOrder(0.0);
	
	layer1_Layer:AddGameObject(Cage_8_Sprite)

	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\Ball.png",1,1,1.0);
	anim0:SetName("Ball");
	Ball1_11_Sprite = Sprite(anim0);

	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		dynamicCollisionData =  DynamicObject();
		dynamicCollisionData:AddCollisionData(collisionActor1);
		dynamicCollisionData:SetCollisionType(true);
		dynamicCollisionData:SetCollisionThickness(0.0);
		dynamicCollisionData:SetBoundingRectangleCheckingTileMap(true);
		dynamicCollisionData:SetZCollision(2);
		dynamicCollisionData:SetCanCollid(0,true);
		dynamicCollisionData:SetUpdateOnIdle(false);
		Ball1_11_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	Ball1_11_Sprite:SetName("Ball1");
	Ball1_11_Sprite:SetCollisionActorIndex(1);
	Ball1_11_Sprite:SetOpacity(1.0);
	Ball1_11_Sprite:Play(true);
	Ball1_11_Sprite:SetPosition(Point2D(-300.0,250.0));
	Ball1_11_Sprite:SetCurrentAnimationIndex(0);
	Ball1_11_Sprite:SetCurrentFrameIndex(0);
	Ball1_11_Sprite:SetLoop(true);
	Ball1_11_Sprite:SetAnimationSpeed(1.0);
	Ball1_11_Sprite:SetFlipHorizontal(false);
	Ball1_11_Sprite:SetFlipVertical(false);
	Ball1_11_Sprite:SetLifeTime(0.0);
	Ball1_11_Sprite:SetVisible(true);
	Ball1_11_Sprite:SetRotationAngle(0.0);
	Ball1_11_Sprite:SetScale(1.0, 1.0);
	Ball1_11_Sprite:SetCenter(Point2D(0.0,0.0));
	Ball1_11_Sprite:SetZOrder(0.0);
	
	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		Ball1_11_Sprite:SetCenter(Point2D(0.0,0.0));
		Ball1_11_Sprite:AddPhysicalProperties(MassProperties(0.01,1.0,Point2D(0.0,0.0)),Physics.ODESolverMethodEuler);
		Ball1_11_Sprite:AddForce(ConstantForce(Vector2D(1.0,-1.0),0.2));
		Ball1_11_Sprite:SetVelocity(Vector2D(0.0,0.0));
		Ball1_11_Sprite:SetAngularVelocity(0.0);
	end

	layer1_Layer:AddGameObject(Ball1_11_Sprite)

	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\Ball.png",1,1,1.0);
	anim0:SetName("Ball");
	Ball2_12_Sprite = Sprite(anim0);

	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		dynamicCollisionData =  DynamicObject();
		dynamicCollisionData:AddCollisionData(collisionActor1);
		dynamicCollisionData:SetCollisionType(true);
		dynamicCollisionData:SetCollisionThickness(0.0);
		dynamicCollisionData:SetBoundingRectangleCheckingTileMap(true);
		dynamicCollisionData:SetZCollision(3);
		dynamicCollisionData:SetCanCollid(0,true);
		dynamicCollisionData:SetUpdateOnIdle(false);
		Ball2_12_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	Ball2_12_Sprite:SetName("Ball2");
	Ball2_12_Sprite:SetCollisionActorIndex(1);
	Ball2_12_Sprite:SetOpacity(1.0);
	Ball2_12_Sprite:Play(true);
	Ball2_12_Sprite:SetPosition(Point2D(-170.0,-50.0));
	Ball2_12_Sprite:SetCurrentAnimationIndex(0);
	Ball2_12_Sprite:SetCurrentFrameIndex(0);
	Ball2_12_Sprite:SetLoop(true);
	Ball2_12_Sprite:SetAnimationSpeed(1.0);
	Ball2_12_Sprite:SetFlipHorizontal(false);
	Ball2_12_Sprite:SetFlipVertical(false);
	Ball2_12_Sprite:SetLifeTime(0.0);
	Ball2_12_Sprite:SetVisible(true);
	Ball2_12_Sprite:SetRotationAngle(0.0);
	Ball2_12_Sprite:SetScale(1.0, 1.0);
	Ball2_12_Sprite:SetCenter(Point2D(0.0,0.0));
	Ball2_12_Sprite:SetZOrder(0.0);
	
	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		Ball2_12_Sprite:SetCenter(Point2D(0.0,0.0));
		Ball2_12_Sprite:AddPhysicalProperties(MassProperties(0.01,1.0,Point2D(0.0,0.0)),Physics.ODESolverMethodEuler);
		Ball2_12_Sprite:AddForce(ConstantForce(Vector2D(1.0,1.0),0.2));
		Ball2_12_Sprite:SetVelocity(Vector2D(0.0,0.0));
		Ball2_12_Sprite:SetAngularVelocity(0.0);
	end

	layer1_Layer:AddGameObject(Ball2_12_Sprite)



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


	camera0_2_Camera = Camera(45.0);
	camera0_2_Camera:SetName("camera0");
	camera0_2_Camera:SetPosition(Point2D(0.0,0.0));
	layer2_Layer:AddGameObject(camera0_2_Camera);


	Viewport0_Viewport = Viewport(0, 0, 800, 600);
	Viewport0_Viewport:SetClearColor(Color(0.2509804 ,0.2509804 ,0.2509804));
	Viewport0_Viewport:SetCamera(camera0_2_Camera);

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
	camera0_2_Camera = 0;

	--Texts

	--Sounds
	BGM_13_Sound = 0;

	--TileMaps

	--Sprites
	Map_5_Sprite = 0;
	Ball0_6_Sprite = 0;
	Cage_8_Sprite = 0;
	Ball1_11_Sprite = 0;
	Ball2_12_Sprite = 0;

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
