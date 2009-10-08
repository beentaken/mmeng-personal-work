
--CollisionActors
collisionActor0 = 0;
collisionActor1 = 0;
collisionActor2 = 0;
collisionActor3 = 0;
collisionActor4 = 0;


--Cameras
camera0_2_Camera = 0;


--Texts
timer_11_Text = 0;
score_12_Text = 0;
multiplier_13_Text = 0;

--Sounds

--TileMaps

--Sprites
background_4_Sprite = 0;
map_5_Sprite = 0;
ship_6_Sprite = 0;
bullet_8_Sprite = 0;
homingEnemy_9_Sprite = 0;

--ParticleSystems
enemyExplode_10_ParticleSystem = 0;

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
	collisionFrame:AddCollisionData(Point2D(-26.0,20.0),Point2D(23.0,20.0),0,true);
	collisionFrame:AddCollisionData(Point2D(-26.0,-20.0),Point2D(-26.0,20.0),0,true);
	collisionFrame:AddCollisionData(Point2D(23.0,20.0),Point2D(23.0,-20.0),0,true);
	collisionFrame:AddCollisionData(Point2D(23.0,-20.0),Point2D(-26.0,-20.0),0,true);
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
	collisionFrame:AddCollisionData(Point2D(0,0),25,0,true);
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
	timer_11_Text= Text("MyText",Game.Get():GetDirectory().."\\Resources\\Fonts\\DefaultFont\\DefaultFont");
	timer_11_Text:SetName("timer");
	timer_11_Text:SetPosition(Point2D(-50.0,270.0));
	timer_11_Text:SetLifeTime(0.0);
	timer_11_Text:SetVisible(true);
	timer_11_Text:SetRotationAngle(0.0);
	timer_11_Text:SetScale(1.0,1.0);
	timer_11_Text:SetCenter(Point2D(0.0,0.0));
	timer_11_Text:SetOpacity(1.0);
	timer_11_Text:SetZOrder(0.0);
	timer_11_Text:SetHUDObject(true);layer0_Layer:AddGameObject(timer_11_Text)

	score_12_Text= Text("0",Game.Get():GetDirectory().."\\Resources\\Fonts\\DefaultFont\\DefaultFont");
	score_12_Text:SetName("score");
	score_12_Text:SetPosition(Point2D(-380.0,-300.0));
	score_12_Text:SetLifeTime(0.0);
	score_12_Text:SetVisible(true);
	score_12_Text:SetRotationAngle(0.0);
	score_12_Text:SetScale(1.0,1.0);
	score_12_Text:SetCenter(Point2D(0.0,0.0));
	score_12_Text:SetOpacity(1.0);
	score_12_Text:SetZOrder(0.0);
	score_12_Text:SetHUDObject(true);layer0_Layer:AddGameObject(score_12_Text)

	multiplier_13_Text= Text("x1",Game.Get():GetDirectory().."\\Resources\\Fonts\\DefaultFont\\DefaultFont");
	multiplier_13_Text:SetName("multiplier");
	multiplier_13_Text:SetPosition(Point2D(-380.0,-260.0));
	multiplier_13_Text:SetLifeTime(0.0);
	multiplier_13_Text:SetVisible(true);
	multiplier_13_Text:SetRotationAngle(0.0);
	multiplier_13_Text:SetScale(1.0,1.0);
	multiplier_13_Text:SetCenter(Point2D(0.0,0.0));
	multiplier_13_Text:SetOpacity(1.0);
	multiplier_13_Text:SetZOrder(0.0);
	multiplier_13_Text:SetHUDObject(true);layer0_Layer:AddGameObject(multiplier_13_Text)



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
	background_4_Sprite = Sprite(anim0);

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
		background_4_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	background_4_Sprite:SetName("background");
	background_4_Sprite:SetCollisionActorIndex(0);
	background_4_Sprite:SetOpacity(1.0);
	background_4_Sprite:Play(true);
	background_4_Sprite:SetPosition(Point2D(0.0,0.0));
	background_4_Sprite:SetCurrentAnimationIndex(0);
	background_4_Sprite:SetCurrentFrameIndex(0);
	background_4_Sprite:SetLoop(true);
	background_4_Sprite:SetAnimationSpeed(1.0);
	background_4_Sprite:SetFlipHorizontal(false);
	background_4_Sprite:SetFlipVertical(false);
	background_4_Sprite:SetLifeTime(0.0);
	background_4_Sprite:SetVisible(true);
	background_4_Sprite:SetRotationAngle(0.0);
	background_4_Sprite:SetScale(1.0, 1.0);
	background_4_Sprite:SetCenter(Point2D(0.0,0.0));
	background_4_Sprite:SetZOrder(0.0);
	
	layer1_Layer:AddGameObject(background_4_Sprite)

	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\Map.png",1,1,1.0);
	anim0:SetName("Map");
	map_5_Sprite = Sprite(anim0);

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
		map_5_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	map_5_Sprite:SetName("map");
	map_5_Sprite:SetCollisionActorIndex(1);
	map_5_Sprite:SetOpacity(1.0);
	map_5_Sprite:Play(true);
	map_5_Sprite:SetPosition(Point2D(0.0,0.0));
	map_5_Sprite:SetCurrentAnimationIndex(0);
	map_5_Sprite:SetCurrentFrameIndex(0);
	map_5_Sprite:SetLoop(true);
	map_5_Sprite:SetAnimationSpeed(1.0);
	map_5_Sprite:SetFlipHorizontal(false);
	map_5_Sprite:SetFlipVertical(false);
	map_5_Sprite:SetLifeTime(0.0);
	map_5_Sprite:SetVisible(true);
	map_5_Sprite:SetRotationAngle(0.0);
	map_5_Sprite:SetScale(1.0, 1.0);
	map_5_Sprite:SetCenter(Point2D(0.0,0.0));
	map_5_Sprite:SetZOrder(0.0);
	
	layer1_Layer:AddGameObject(map_5_Sprite)

	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\Ship.png",1,1,1.0);
	anim0:SetName("Ship");
	ship_6_Sprite = Ship(anim0);

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
		ship_6_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	ship_6_Sprite:SetName("ship");
	ship_6_Sprite:SetCollisionActorIndex(2);
	ship_6_Sprite:SetOpacity(1.0);
	ship_6_Sprite:Play(true);
	ship_6_Sprite:SetPosition(Point2D(0.0,0.0));
	ship_6_Sprite:SetCurrentAnimationIndex(0);
	ship_6_Sprite:SetCurrentFrameIndex(0);
	ship_6_Sprite:SetLoop(true);
	ship_6_Sprite:SetAnimationSpeed(1.0);
	ship_6_Sprite:SetFlipHorizontal(false);
	ship_6_Sprite:SetFlipVertical(false);
	ship_6_Sprite:SetLifeTime(0.0);
	ship_6_Sprite:SetVisible(true);
	ship_6_Sprite:SetRotationAngle(0.0);
	ship_6_Sprite:SetScale(1.0, 1.0);
	ship_6_Sprite:SetCenter(Point2D(0.0,0.0));
	ship_6_Sprite:SetZOrder(0.0);
	
	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		ship_6_Sprite:SetCenter(Point2D(0.0,0.0));
		ship_6_Sprite:AddPhysicalProperties(MassProperties(10.0,0.0,Point2D(0.0,0.0)),Physics.ODESolverMethodEuler);
		ship_6_Sprite:SetVelocity(Vector2D(0.0,0.0));
		ship_6_Sprite:SetAngularVelocity(0.0);
	end

	layer1_Layer:AddGameObject(ship_6_Sprite)

	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\Bullet.png",1,1,1.0);
	anim0:SetName("Bullet");
	bullet_8_Sprite = Bullet(anim0);

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
		bullet_8_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	bullet_8_Sprite:SetName("bullet");
	bullet_8_Sprite:SetCollisionActorIndex(3);
	bullet_8_Sprite:SetOpacity(1.0);
	bullet_8_Sprite:Play(true);
	bullet_8_Sprite:SetPosition(Point2D(0.0,-600.0));
	bullet_8_Sprite:SetCurrentAnimationIndex(0);
	bullet_8_Sprite:SetCurrentFrameIndex(0);
	bullet_8_Sprite:SetLoop(true);
	bullet_8_Sprite:SetAnimationSpeed(1.0);
	bullet_8_Sprite:SetFlipHorizontal(false);
	bullet_8_Sprite:SetFlipVertical(false);
	bullet_8_Sprite:SetLifeTime(0.0);
	bullet_8_Sprite:SetVisible(true);
	bullet_8_Sprite:SetRotationAngle(0.0);
	bullet_8_Sprite:SetScale(1.0, 1.0);
	bullet_8_Sprite:SetCenter(Point2D(0.0,0.0));
	bullet_8_Sprite:SetZOrder(0.0);
	
	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		bullet_8_Sprite:SetCenter(Point2D(0.0,0.0));
		bullet_8_Sprite:AddPhysicalProperties(MassProperties(0.01,1.0,Point2D(0.0,0.0)),Physics.ODESolverMethodEuler);
		bullet_8_Sprite:SetVelocity(Vector2D(0.0,0.0));
		bullet_8_Sprite:SetAngularVelocity(0.0);
	end

	layer1_Layer:AddGameObject(bullet_8_Sprite)

	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\HomingEnemy.png",1,1,1.0);
	anim0:SetName("HomingEnemy");
	homingEnemy_9_Sprite = HomingEnemy(anim0);

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
		homingEnemy_9_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	homingEnemy_9_Sprite:SetName("homingEnemy");
	homingEnemy_9_Sprite:SetCollisionActorIndex(4);
	homingEnemy_9_Sprite:SetOpacity(1.0);
	homingEnemy_9_Sprite:Play(true);
	homingEnemy_9_Sprite:SetPosition(Point2D(200.0,100.0));
	homingEnemy_9_Sprite:SetCurrentAnimationIndex(0);
	homingEnemy_9_Sprite:SetCurrentFrameIndex(0);
	homingEnemy_9_Sprite:SetLoop(true);
	homingEnemy_9_Sprite:SetAnimationSpeed(1.0);
	homingEnemy_9_Sprite:SetFlipHorizontal(false);
	homingEnemy_9_Sprite:SetFlipVertical(false);
	homingEnemy_9_Sprite:SetLifeTime(0.0);
	homingEnemy_9_Sprite:SetVisible(true);
	homingEnemy_9_Sprite:SetRotationAngle(0.0);
	homingEnemy_9_Sprite:SetScale(1.0, 1.0);
	homingEnemy_9_Sprite:SetCenter(Point2D(0.0,0.0));
	homingEnemy_9_Sprite:SetZOrder(0.0);
	
	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		homingEnemy_9_Sprite:SetCenter(Point2D(0.0,0.0));
		homingEnemy_9_Sprite:AddPhysicalProperties(MassProperties(0.01,1.0,Point2D(0.0,0.0)),Physics.ODESolverMethodEuler);
		homingEnemy_9_Sprite:SetVelocity(Vector2D(0.0,0.0));
		homingEnemy_9_Sprite:SetAngularVelocity(0.0);
	end

	layer1_Layer:AddGameObject(homingEnemy_9_Sprite)



	--ParticleSystems Setters
	pe = PointEmitter(Point2D(0.0, 0.0), 0.0, 360.0);
	enemyExplode_10_ParticleSystem = ParticleSystem(Game.Get():GetDirectory().."\\Resources\\ParticleSystems\\Particle_Texture.png", 128, 256, Vector2D(0.0, 0.0));
	enemyExplode_10_ParticleSystem:SetEmitter(pe);

	enemyExplode_10_ParticleSystem:SetName("enemyExplode");
	enemyExplode_10_ParticleSystem:SetLifeTime(0.0);
	enemyExplode_10_ParticleSystem:SetZOrder(0.0);
	enemyExplode_10_ParticleSystem:SetPosition(0.0, 0.0);
	enemyExplode_10_ParticleSystem:SetRotationAngle(0.0);
	enemyExplode_10_ParticleSystem:SetScale(0.4, 0.4);
	enemyExplode_10_ParticleSystem:SetCenter(Point2D(0.0,0.0));
	enemyExplode_10_ParticleSystem:SetVisible(false);
	enemyExplode_10_ParticleSystem:SetRecycleParticles(true);
	enemyExplode_10_ParticleSystem:SetEmissionRate(64.0, 64.0);
	enemyExplode_10_ParticleSystem:SetSrcBlendFactor(BlendFactor.BlendFactorSrcAlpha);
	enemyExplode_10_ParticleSystem:SetDstBlendFactor(BlendFactor.BlendFactorInvSrcAlpha);
	enemyExplode_10_ParticleSystem:SetParticleStartingColor(Color(1.0, 1.0, 0.2, 1.0), Color(1.0, 0.4, 0.0, 1.0));
	enemyExplode_10_ParticleSystem:SetParticleEndingColor(Color(1.0, 1.0, 0.4, 0.0), Color(0.8, 0.8, 0.0, 0.0));
	enemyExplode_10_ParticleSystem:SetParticleLifeTime(0.0, 0.0);
	enemyExplode_10_ParticleSystem:SetParticleSpeed(0.0, 100.0);
	enemyExplode_10_ParticleSystem:SetParticleDirection(ParticleDirection.VelocityDirection);
	enemyExplode_10_ParticleSystem:SetParticleStartingScale(Vector2D(1.0, 1.0), Vector2D(1.0, 1.0));
	enemyExplode_10_ParticleSystem:SetParticleEndingScale(Vector2D(1.0, 1.0), Vector2D(1.0, 1.0));
	enemyExplode_10_ParticleSystem:SetUseLocalCoordinates(true);
	enemyExplode_10_ParticleSystem:WarmUp(0.0);
	layer1_Layer:AddGameObject(enemyExplode_10_ParticleSystem)



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
	timer_11_Text = 0;
	score_12_Text = 0;
	multiplier_13_Text = 0;

	--Sounds

	--TileMaps

	--Sprites
	background_4_Sprite = 0;
	map_5_Sprite = 0;
	ship_6_Sprite = 0;
	bullet_8_Sprite = 0;
	homingEnemy_9_Sprite = 0;

	--ParticleSystems
	enemyExplode_10_ParticleSystem = 0;

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
