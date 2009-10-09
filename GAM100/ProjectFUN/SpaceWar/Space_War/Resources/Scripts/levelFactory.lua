
--CollisionActors
collisionActor0 = 0;
collisionActor1 = 0;
collisionActor2 = 0;
collisionActor3 = 0;
collisionActor4 = 0;


--Cameras
camera0_2_Camera = 0;


--Texts
timer_10_Text = 0;

--Sounds

--TileMaps

--Sprites
Background_3_Sprite = 0;
Map_4_Sprite = 0;
Ship_5_Sprite = 0;
Bullet_7_Sprite = 0;
HomingEnemy_8_Sprite = 0;

--ParticleSystems
enemyExplode_9_ParticleSystem = 0;

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

	collisionFrame:SetBoundingRectangle(FunRect(512,-640,640,-512)); 
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

	collisionFrame:SetBoundingRectangle(FunRect(512,-640,640,-512)); 
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

	collisionFrame:SetBoundingRectangle(FunRect(24,-28,28,-24)); 
	collisionFrame:AddCollisionData(Point2D(-27.0,23.0),Point2D(28.0,23.0),0,true);
	collisionFrame:AddCollisionData(Point2D(-27.0,-23.0),Point2D(-27.0,23.0),0,true);
	collisionFrame:AddCollisionData(Point2D(28.0,23.0),Point2D(28.0,-23.0),0,true);
	collisionFrame:AddCollisionData(Point2D(28.0,-23.0),Point2D(-27.0,-23.0),0,true);
	collisionAnimation:AddCollisionFrame(collisionFrame);


	collisionActor2:AddCollisionAnimation(collisionAnimation);

	-- Adding CollisionActor to Game --
	Game.Get():AddCollisionAssets(collisionActor2);
end

function AddCollisionActors3()

	collisionActor3 = CollisionActor();


	---- Adding New Animation 0 ----
	collisionAnimation =  CollisionAnimation();


	-------- New Frame 0 --------
	collisionFrame = CollisionFrame();

	collisionFrame:SetBoundingRectangle(FunRect(8,-8,8,-8)); 
	collisionFrame:AddCollisionData(Point2D(0,0),4,0,true);
	collisionAnimation:AddCollisionFrame(collisionFrame);


	collisionActor3:AddCollisionAnimation(collisionAnimation);

	-- Adding CollisionActor to Game --
	Game.Get():AddCollisionAssets(collisionActor3);
end

function AddCollisionActors4()

	collisionActor4 = CollisionActor();


	---- Adding New Animation 0 ----
	collisionAnimation =  CollisionAnimation();


	-------- New Frame 0 --------
	collisionFrame = CollisionFrame();

	collisionFrame:SetBoundingRectangle(FunRect(188,-240,240,-188)); 
	collisionFrame:AddCollisionData(Point2D(0,3),20,0,true);
	collisionAnimation:AddCollisionFrame(collisionFrame);


	collisionActor4:AddCollisionAnimation(collisionAnimation);

	-- Adding CollisionActor to Game --
	Game.Get():AddCollisionAssets(collisionActor4);
end

function AddCollisionActors()
	AddCollisionActors0()
	AddCollisionActors1()
	AddCollisionActors2()
	AddCollisionActors3()
	AddCollisionActors4()
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
	timer_10_Text= Text("MyText",Game.Get():GetDirectory().."\\Resources\\Fonts\\DefaultFont\\DefaultFont");
	timer_10_Text:SetName("timer");
	timer_10_Text:SetPosition(Point2D(-50.0,270.0));
	timer_10_Text:SetLifeTime(0.0);
	timer_10_Text:SetVisible(true);
	timer_10_Text:SetRotationAngle(0.0);
	timer_10_Text:SetScale(1.0,1.0);
	timer_10_Text:SetCenter(Point2D(0.0,0.0));
	timer_10_Text:SetOpacity(1.0);
	timer_10_Text:SetZOrder(0.0);
	timer_10_Text:SetHUDObject(true);layer0_Layer:AddGameObject(timer_10_Text)



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

	--Sprites Setters
	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\Background.png",1,1,1.0);
	anim0:SetName("Background");
	Background_3_Sprite = Sprite(anim0);

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
		Background_3_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	Background_3_Sprite:SetName("Background");
	Background_3_Sprite:SetCollisionActorIndex(0);
	Background_3_Sprite:SetOpacity(1.0);
	Background_3_Sprite:Play(true);
	Background_3_Sprite:SetPosition(Point2D(0.0,0.0));
	Background_3_Sprite:SetCurrentAnimationIndex(0);
	Background_3_Sprite:SetCurrentFrameIndex(0);
	Background_3_Sprite:SetLoop(true);
	Background_3_Sprite:SetAnimationSpeed(1.0);
	Background_3_Sprite:SetFlipHorizontal(false);
	Background_3_Sprite:SetFlipVertical(false);
	Background_3_Sprite:SetLifeTime(0.0);
	Background_3_Sprite:SetVisible(true);
	Background_3_Sprite:SetRotationAngle(0.0);
	Background_3_Sprite:SetScale(1.0, 1.0);
	Background_3_Sprite:SetCenter(Point2D(0.0,0.0));
	Background_3_Sprite:SetZOrder(0.0);
	
	layer1_Layer:AddGameObject(Background_3_Sprite)

	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\Map.png",1,1,1.0);
	anim0:SetName("Map");
	Map_4_Sprite = Sprite(anim0);

	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		dynamicCollisionData =  DynamicObject();
		dynamicCollisionData:AddCollisionData(collisionActor1);
		dynamicCollisionData:SetCollisionType(false);
		dynamicCollisionData:SetCollisionThickness(0.0);
		dynamicCollisionData:SetBoundingRectangleCheckingTileMap(true);
		dynamicCollisionData:SetZCollision(0);
		dynamicCollisionData:SetCanCollid(0,true);
		dynamicCollisionData:SetUpdateOnIdle(false);
		Map_4_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	Map_4_Sprite:SetName("Map");
	Map_4_Sprite:SetCollisionActorIndex(1);
	Map_4_Sprite:SetOpacity(1.0);
	Map_4_Sprite:Play(true);
	Map_4_Sprite:SetPosition(Point2D(0.0,0.0));
	Map_4_Sprite:SetCurrentAnimationIndex(0);
	Map_4_Sprite:SetCurrentFrameIndex(0);
	Map_4_Sprite:SetLoop(true);
	Map_4_Sprite:SetAnimationSpeed(1.0);
	Map_4_Sprite:SetFlipHorizontal(false);
	Map_4_Sprite:SetFlipVertical(false);
	Map_4_Sprite:SetLifeTime(0.0);
	Map_4_Sprite:SetVisible(true);
	Map_4_Sprite:SetRotationAngle(0.0);
	Map_4_Sprite:SetScale(1.0, 1.0);
	Map_4_Sprite:SetCenter(Point2D(0.0,0.0));
	Map_4_Sprite:SetZOrder(0.0);
	
	layer1_Layer:AddGameObject(Map_4_Sprite)

	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\Ship.png",1,1,1.0);
	anim0:SetName("Ship");
	Ship_5_Sprite = Ship(anim0);

	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		dynamicCollisionData =  DynamicObject();
		dynamicCollisionData:AddCollisionData(collisionActor2);
		dynamicCollisionData:SetCollisionType(true);
		dynamicCollisionData:SetCollisionThickness(2.0);
		dynamicCollisionData:SetBoundingRectangleCheckingTileMap(true);
		dynamicCollisionData:SetZCollision(0);
		dynamicCollisionData:SetCanCollid(0,true);
		dynamicCollisionData:SetCanCollid(1,true);
		dynamicCollisionData:SetUpdateOnIdle(false);
		Ship_5_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	Ship_5_Sprite:SetName("Ship");
	Ship_5_Sprite:SetCollisionActorIndex(2);
	Ship_5_Sprite:SetOpacity(1.0);
	Ship_5_Sprite:Play(true);
	Ship_5_Sprite:SetPosition(Point2D(0.0,0.0));
	Ship_5_Sprite:SetCurrentAnimationIndex(0);
	Ship_5_Sprite:SetCurrentFrameIndex(0);
	Ship_5_Sprite:SetLoop(true);
	Ship_5_Sprite:SetAnimationSpeed(1.0);
	Ship_5_Sprite:SetFlipHorizontal(false);
	Ship_5_Sprite:SetFlipVertical(false);
	Ship_5_Sprite:SetLifeTime(0.0);
	Ship_5_Sprite:SetVisible(true);
	Ship_5_Sprite:SetRotationAngle(0.0);
	Ship_5_Sprite:SetScale(1.0, 1.0);
	Ship_5_Sprite:SetCenter(Point2D(0.0,0.0));
	Ship_5_Sprite:SetZOrder(0.0);
	
	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		Ship_5_Sprite:SetCenter(Point2D(0.0,0.0));
		Ship_5_Sprite:AddPhysicalProperties(MassProperties(10.0,0.0,Point2D(0.0,0.0)),Physics.ODESolverMethodEuler);
		Ship_5_Sprite:SetVelocity(Vector2D(0.0,0.0));
		Ship_5_Sprite:SetAngularVelocity(0.0);
	end

	layer1_Layer:AddGameObject(Ship_5_Sprite)

	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\Bullet.png",1,1,1.0);
	anim0:SetName("Bullet");
	Bullet_7_Sprite = Bullet(anim0);

	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		dynamicCollisionData =  DynamicObject();
		dynamicCollisionData:AddCollisionData(collisionActor3);
		dynamicCollisionData:SetCollisionType(true);
		dynamicCollisionData:SetCollisionThickness(0.0);
		dynamicCollisionData:SetBoundingRectangleCheckingTileMap(true);
		dynamicCollisionData:SetZCollision(2);
		dynamicCollisionData:SetCanCollid(1,true);
		dynamicCollisionData:SetUpdateOnIdle(false);
		Bullet_7_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	Bullet_7_Sprite:SetName("Bullet");
	Bullet_7_Sprite:SetCollisionActorIndex(3);
	Bullet_7_Sprite:SetOpacity(1.0);
	Bullet_7_Sprite:Play(true);
	Bullet_7_Sprite:SetPosition(Point2D(0.0,-600.0));
	Bullet_7_Sprite:SetCurrentAnimationIndex(0);
	Bullet_7_Sprite:SetCurrentFrameIndex(0);
	Bullet_7_Sprite:SetLoop(true);
	Bullet_7_Sprite:SetAnimationSpeed(1.0);
	Bullet_7_Sprite:SetFlipHorizontal(false);
	Bullet_7_Sprite:SetFlipVertical(false);
	Bullet_7_Sprite:SetLifeTime(0.0);
	Bullet_7_Sprite:SetVisible(true);
	Bullet_7_Sprite:SetRotationAngle(0.0);
	Bullet_7_Sprite:SetScale(1.0, 1.0);
	Bullet_7_Sprite:SetCenter(Point2D(0.0,0.0));
	Bullet_7_Sprite:SetZOrder(0.0);
	
	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		Bullet_7_Sprite:SetCenter(Point2D(0.0,0.0));
		Bullet_7_Sprite:AddPhysicalProperties(MassProperties(0.01,1.0,Point2D(0.0,0.0)),Physics.ODESolverMethodEuler);
		Bullet_7_Sprite:SetVelocity(Vector2D(0.0,0.0));
		Bullet_7_Sprite:SetAngularVelocity(0.0);
	end

	layer1_Layer:AddGameObject(Bullet_7_Sprite)

	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\HomingEnemy.png",1,1,1.0);
	anim0:SetName("HomingEnemy");
	HomingEnemy_8_Sprite = HomingEnemy(anim0);

	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		dynamicCollisionData =  DynamicObject();
		dynamicCollisionData:AddCollisionData(collisionActor4);
		dynamicCollisionData:SetCollisionType(true);
		dynamicCollisionData:SetCollisionThickness(0.0);
		dynamicCollisionData:SetBoundingRectangleCheckingTileMap(true);
		dynamicCollisionData:SetZCollision(1);
		dynamicCollisionData:SetCanCollid(0,true);
		dynamicCollisionData:SetCanCollid(2,true);
		dynamicCollisionData:SetUpdateOnIdle(false);
		HomingEnemy_8_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	HomingEnemy_8_Sprite:SetName("HomingEnemy");
	HomingEnemy_8_Sprite:SetCollisionActorIndex(4);
	HomingEnemy_8_Sprite:SetOpacity(1.0);
	HomingEnemy_8_Sprite:Play(true);
	HomingEnemy_8_Sprite:SetPosition(Point2D(200.0,100.0));
	HomingEnemy_8_Sprite:SetCurrentAnimationIndex(0);
	HomingEnemy_8_Sprite:SetCurrentFrameIndex(0);
	HomingEnemy_8_Sprite:SetLoop(true);
	HomingEnemy_8_Sprite:SetAnimationSpeed(1.0);
	HomingEnemy_8_Sprite:SetFlipHorizontal(false);
	HomingEnemy_8_Sprite:SetFlipVertical(false);
	HomingEnemy_8_Sprite:SetLifeTime(0.0);
	HomingEnemy_8_Sprite:SetVisible(true);
	HomingEnemy_8_Sprite:SetRotationAngle(0.0);
	HomingEnemy_8_Sprite:SetScale(1.0, 1.0);
	HomingEnemy_8_Sprite:SetCenter(Point2D(0.0,0.0));
	HomingEnemy_8_Sprite:SetZOrder(0.0);
	
	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		HomingEnemy_8_Sprite:SetCenter(Point2D(0.0,0.0));
		HomingEnemy_8_Sprite:AddPhysicalProperties(MassProperties(0.01,1.0,Point2D(0.0,0.0)),Physics.ODESolverMethodEuler);
		HomingEnemy_8_Sprite:SetVelocity(Vector2D(0.0,0.0));
		HomingEnemy_8_Sprite:SetAngularVelocity(0.0);
	end

	layer1_Layer:AddGameObject(HomingEnemy_8_Sprite)



	--ParticleSystems Setters
	pe = PointEmitter(Point2D(0.0, 0.0), 0.0, 360.0);
	enemyExplode_9_ParticleSystem = ParticleSystem(Game.Get():GetDirectory().."\\Resources\\ParticleSystems\\Particle_Texture.png", 128, 256, Vector2D(0.0, 0.0));
	enemyExplode_9_ParticleSystem:SetEmitter(pe);

	enemyExplode_9_ParticleSystem:SetName("enemyExplode");
	enemyExplode_9_ParticleSystem:SetLifeTime(0.0);
	enemyExplode_9_ParticleSystem:SetZOrder(0.0);
	enemyExplode_9_ParticleSystem:SetPosition(0.0, 0.0);
	enemyExplode_9_ParticleSystem:SetRotationAngle(0.0);
	enemyExplode_9_ParticleSystem:SetScale(0.4, 0.4);
	enemyExplode_9_ParticleSystem:SetCenter(Point2D(0.0,0.0));
	enemyExplode_9_ParticleSystem:SetVisible(false);
	enemyExplode_9_ParticleSystem:SetRecycleParticles(true);
	enemyExplode_9_ParticleSystem:SetEmissionRate(64.0, 64.0);
	enemyExplode_9_ParticleSystem:SetSrcBlendFactor(BlendFactor.BlendFactorSrcAlpha);
	enemyExplode_9_ParticleSystem:SetDstBlendFactor(BlendFactor.BlendFactorInvSrcAlpha);
	enemyExplode_9_ParticleSystem:SetParticleStartingColor(Color(1.0, 1.0, 0.4, 1.0), Color(1.0, 0.6, 0.0, 1.0));
	enemyExplode_9_ParticleSystem:SetParticleEndingColor(Color(1.0, 1.0, 0.2, 0.0), Color(1.0, 1.0, 0.2, 0.0));
	enemyExplode_9_ParticleSystem:SetParticleLifeTime(0.0, 0.0);
	enemyExplode_9_ParticleSystem:SetParticleSpeed(0.0, 100.0);
	enemyExplode_9_ParticleSystem:SetParticleDirection(ParticleDirection.VelocityDirection);
	enemyExplode_9_ParticleSystem:SetParticleStartingScale(Vector2D(1.0, 1.0), Vector2D(1.0, 1.0));
	enemyExplode_9_ParticleSystem:SetParticleEndingScale(Vector2D(1.0, 1.0), Vector2D(1.0, 1.0));
	enemyExplode_9_ParticleSystem:SetUseLocalCoordinates(false);
	enemyExplode_9_ParticleSystem:WarmUp(0.0);
	layer1_Layer:AddGameObject(enemyExplode_9_ParticleSystem)



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
	level0_Level = Level0();
	level0_Level:SetName("level0");
	level0_Level:SetClearBackBuffer(false);

	layer0_Layer = Layer(0.0);
	layer0_Layer:SetName("level0_HUD");

	layer0_Layer:SetCollisionProperties(Point2D(-400,-300),800,600);
	layer1_Layer = Layer(0.0);
	layer1_Layer:SetName("layer1");
	layer1_Layer:SetScale(1.0,1.0);
	layer1_Layer:SetRotation(0.0);
	layer1_Layer:SetCollisionProperties(Point2D(-640,-608),1280,1120);

	layer2_Layer = Layer(724.2641);
	layer2_Layer:SetName("layer2");
	layer2_Layer:SetScale(1.0,1.0);
	layer2_Layer:SetRotation(0.0);
	layer2_Layer:SetCollisionProperties(Point2D(-400,-300),800,600);


	camera0_2_Camera = ShipCam(45.0);
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
	timer_10_Text = 0;

	--Sounds

	--TileMaps

	--Sprites
	Background_3_Sprite = 0;
	Map_4_Sprite = 0;
	Ship_5_Sprite = 0;
	Bullet_7_Sprite = 0;
	HomingEnemy_8_Sprite = 0;

	--ParticleSystems
	enemyExplode_9_ParticleSystem = 0;

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
