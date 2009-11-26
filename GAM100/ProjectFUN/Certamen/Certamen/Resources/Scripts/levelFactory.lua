
--CollisionActors
collisionActor0 = 0;
collisionActor1 = 0;
collisionActor2 = 0;
collisionActor3 = 0;


--Cameras
camera0_2_Camera = 0;


--Texts
player1power_12_Text = 0;

--Sounds

--TileMaps

--Sprites
background_3_Sprite = 0;
roundBullet_8_Sprite = 0;
player2proxy_10_Sprite = 0;
player1proxy_15_Sprite = 0;
player1body_6_Sprite = 0;
player1hitbox_14_Sprite = 0;

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

	collisionFrame:SetBoundingRectangle(FunRect(300,-400,400,-300)); 
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

	collisionFrame:SetBoundingRectangle(FunRect(10,-10,10,-10)); 
	collisionFrame:AddCollisionData(Point2D(0,0),10,0,true);
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

	collisionFrame:SetBoundingRectangle(FunRect(24,-24,24,-24)); 
	collisionFrame:AddCollisionData(Point2D(0,0),10,0,true);
	collisionFrame:AddCollisionData(Point2D(0,0),24,0,true);
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

	collisionFrame:SetBoundingRectangle(FunRect(3,-3,3,-3)); 
	collisionFrame:AddCollisionData(Point2D(0,0),3,0,true);
	collisionAnimation:AddCollisionFrame(collisionFrame);


	collisionActor3:AddCollisionAnimation(collisionAnimation);

	-- Adding CollisionActor to Game --
	Game.Get():AddCollisionAssets(collisionActor3);
end

function AddCollisionActors()
	AddCollisionActors0()
	AddCollisionActors1()
	AddCollisionActors2()
	AddCollisionActors3()
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
	player1power_12_Text= PowerMeter("0",Game.Get():GetDirectory().."\\Resources\\Fonts\\DefaultFont\\DefaultFont");
	player1power_12_Text:SetName("player1power");
	player1power_12_Text:SetPosition(Point2D(-372.0,-269.0));
	player1power_12_Text:SetLifeTime(0.0);
	player1power_12_Text:SetVisible(true);
	player1power_12_Text:SetRotationAngle(0.0);
	player1power_12_Text:SetScale(1.0,1.0);
	player1power_12_Text:SetCenter(Point2D(0.0,0.0));
	player1power_12_Text:SetOpacity(1.0);
	player1power_12_Text:SetZOrder(0.0);
	player1power_12_Text:SetHUDObject(true);layer0_Layer:AddGameObject(player1power_12_Text)



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
	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\background.png",1,1,1.0);
	anim0:SetName("background");
	background_3_Sprite:SetName("background");
	background_3_Sprite:SetCollisionActorIndex(0);
	background_3_Sprite:SetOpacity(1.0);
	background_3_Sprite:Play(true);
	background_3_Sprite:SetPosition(Point2D(0.0,0.0));
	background_3_Sprite:SetCurrentAnimationIndex(0);
	background_3_Sprite:SetCurrentFrameIndex(0);
	background_3_Sprite:SetLoop(true);
	background_3_Sprite:SetAnimationSpeed(1.0);
	background_3_Sprite:SetFlipHorizontal(false);
	background_3_Sprite:SetFlipVertical(false);
	background_3_Sprite:SetLifeTime(0.0);
	background_3_Sprite:SetVisible(true);
	background_3_Sprite:SetRotationAngle(0.0);
	background_3_Sprite:SetScale(1.0, 1.0);
	background_3_Sprite:SetCenter(Point2D(0.0,0.0));
	background_3_Sprite:SetZOrder(0.0);
	
	layer1_Layer:AddGameObject(background_3_Sprite)

	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\Round.png",1,1,1.0);
	anim0:SetName("Round");
	roundBullet_8_Sprite = BulletRound(anim0);

	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		dynamicCollisionData =  DynamicObject();
		dynamicCollisionData:AddCollisionData(collisionActor1);
		dynamicCollisionData:SetCollisionType(true);
		dynamicCollisionData:SetCollisionThickness(2.0);
		dynamicCollisionData:SetBoundingRectangleCheckingTileMap(true);
		dynamicCollisionData:SetZCollision(2);
		dynamicCollisionData:SetCanCollid(0,true);
		dynamicCollisionData:SetUpdateOnIdle(true);
		roundBullet_8_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	roundBullet_8_Sprite:SetName("roundBullet");
	roundBullet_8_Sprite:SetCollisionActorIndex(1);
	roundBullet_8_Sprite:SetOpacity(1.0);
	roundBullet_8_Sprite:Play(true);
	roundBullet_8_Sprite:SetPosition(Point2D(0.0,-280.0));
	roundBullet_8_Sprite:SetCurrentAnimationIndex(0);
	roundBullet_8_Sprite:SetCurrentFrameIndex(0);
	roundBullet_8_Sprite:SetLoop(true);
	roundBullet_8_Sprite:SetAnimationSpeed(1.0);
	roundBullet_8_Sprite:SetFlipHorizontal(false);
	roundBullet_8_Sprite:SetFlipVertical(false);
	roundBullet_8_Sprite:SetLifeTime(0.0);
	roundBullet_8_Sprite:SetVisible(false);
	roundBullet_8_Sprite:SetRotationAngle(0.0);
	roundBullet_8_Sprite:SetScale(1.0, 1.0);
	roundBullet_8_Sprite:SetCenter(Point2D(0.0,0.0));
	roundBullet_8_Sprite:SetZOrder(2.0);
	
	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		roundBullet_8_Sprite:SetCenter(Point2D(0.0,0.0));
		roundBullet_8_Sprite:AddPhysicalProperties(MassProperties(0.0,0.0,Point2D(0.0,0.0)),Physics.ODESolverMethodEuler);
		roundBullet_8_Sprite:SetVelocity(Vector2D(0.0,0.0));
		roundBullet_8_Sprite:SetAngularVelocity(0.0);
	end

	layer1_Layer:AddGameObject(roundBullet_8_Sprite)

	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\Player.png",1,1,1.0);
	anim0:SetName("Player");
	player2proxy_10_Sprite = Sprite(anim0);

	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		dynamicCollisionData =  DynamicObject();
		dynamicCollisionData:AddCollisionData(collisionActor2);
		dynamicCollisionData:SetCollisionType(true);
		dynamicCollisionData:SetCollisionThickness(2.0);
		dynamicCollisionData:SetBoundingRectangleCheckingTileMap(true);
		dynamicCollisionData:SetZCollision(1);
		dynamicCollisionData:SetCanCollid(0,true);
		dynamicCollisionData:SetCanCollid(1,true);
		dynamicCollisionData:SetCanCollid(2,true);
		dynamicCollisionData:SetUpdateOnIdle(true);
		player2proxy_10_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	player2proxy_10_Sprite:SetName("player2proxy");
	player2proxy_10_Sprite:SetCollisionActorIndex(2);
	player2proxy_10_Sprite:SetOpacity(1.0);
	player2proxy_10_Sprite:Play(true);
	player2proxy_10_Sprite:SetPosition(Point2D(-200.0,230.0));
	player2proxy_10_Sprite:SetCurrentAnimationIndex(0);
	player2proxy_10_Sprite:SetCurrentFrameIndex(0);
	player2proxy_10_Sprite:SetLoop(true);
	player2proxy_10_Sprite:SetAnimationSpeed(1.0);
	player2proxy_10_Sprite:SetFlipHorizontal(false);
	player2proxy_10_Sprite:SetFlipVertical(false);
	player2proxy_10_Sprite:SetLifeTime(0.0);
	player2proxy_10_Sprite:SetVisible(true);
	player2proxy_10_Sprite:SetRotationAngle(0.0);
	player2proxy_10_Sprite:SetScale(1.0, 1.0);
	player2proxy_10_Sprite:SetCenter(Point2D(0.0,0.0));
	player2proxy_10_Sprite:SetZOrder(7.0);
	
	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		player2proxy_10_Sprite:SetCenter(Point2D(0.0,0.0));
		player2proxy_10_Sprite:AddPhysicalProperties(MassProperties(0.0,0.0,Point2D(0.0,0.0)),Physics.ODESolverMethodEuler);
		player2proxy_10_Sprite:SetVelocity(Vector2D(0.0,0.0));
		player2proxy_10_Sprite:SetAngularVelocity(0.0);
	end

	layer1_Layer:AddGameObject(player2proxy_10_Sprite)

	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\Player.png",1,1,1.0);
	anim0:SetName("Player");
	player1proxy_15_Sprite = Sprite(anim0);

	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		dynamicCollisionData =  DynamicObject();
		dynamicCollisionData:AddCollisionData(collisionActor2);
		dynamicCollisionData:SetCollisionType(true);
		dynamicCollisionData:SetCollisionThickness(2.0);
		dynamicCollisionData:SetBoundingRectangleCheckingTileMap(true);
		dynamicCollisionData:SetZCollision(1);
		dynamicCollisionData:SetCanCollid(0,true);
		dynamicCollisionData:SetUpdateOnIdle(true);
		player1proxy_15_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	player1proxy_15_Sprite:SetName("player1proxy");
	player1proxy_15_Sprite:SetCollisionActorIndex(2);
	player1proxy_15_Sprite:SetOpacity(1.0);
	player1proxy_15_Sprite:Play(true);
	player1proxy_15_Sprite:SetPosition(Point2D(200.0,237.0));
	player1proxy_15_Sprite:SetCurrentAnimationIndex(0);
	player1proxy_15_Sprite:SetCurrentFrameIndex(0);
	player1proxy_15_Sprite:SetLoop(true);
	player1proxy_15_Sprite:SetAnimationSpeed(1.0);
	player1proxy_15_Sprite:SetFlipHorizontal(false);
	player1proxy_15_Sprite:SetFlipVertical(false);
	player1proxy_15_Sprite:SetLifeTime(0.0);
	player1proxy_15_Sprite:SetVisible(true);
	player1proxy_15_Sprite:SetRotationAngle(0.0);
	player1proxy_15_Sprite:SetScale(1.0, 1.0);
	player1proxy_15_Sprite:SetCenter(Point2D(0.0,0.0));
	player1proxy_15_Sprite:SetZOrder(7.0);
	
	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		player1proxy_15_Sprite:SetCenter(Point2D(0.0,0.0));
		player1proxy_15_Sprite:AddPhysicalProperties(MassProperties(0.0,0.0,Point2D(0.0,0.0)),Physics.ODESolverMethodEuler);
		player1proxy_15_Sprite:SetVelocity(Vector2D(0.0,0.0));
		player1proxy_15_Sprite:SetAngularVelocity(0.0);
	end

	layer1_Layer:AddGameObject(player1proxy_15_Sprite)

	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\Player.png",1,1,1.0);
	anim0:SetName("Player");
	player1body_6_Sprite = Sprite(anim0);

	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		dynamicCollisionData =  DynamicObject();
		dynamicCollisionData:AddCollisionData(collisionActor2);
		dynamicCollisionData:SetCollisionType(true);
		dynamicCollisionData:SetCollisionThickness(2.0);
		dynamicCollisionData:SetBoundingRectangleCheckingTileMap(true);
		dynamicCollisionData:SetZCollision(1);
		dynamicCollisionData:SetCanCollid(2,true);
		dynamicCollisionData:SetUpdateOnIdle(true);
		player1body_6_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	player1body_6_Sprite:SetName("player1body");
	player1body_6_Sprite:SetCollisionActorIndex(2);
	player1body_6_Sprite:SetOpacity(1.0);
	player1body_6_Sprite:Play(true);
	player1body_6_Sprite:SetPosition(Point2D(-200.0,-230.0));
	player1body_6_Sprite:SetCurrentAnimationIndex(0);
	player1body_6_Sprite:SetCurrentFrameIndex(0);
	player1body_6_Sprite:SetLoop(true);
	player1body_6_Sprite:SetAnimationSpeed(1.0);
	player1body_6_Sprite:SetFlipHorizontal(false);
	player1body_6_Sprite:SetFlipVertical(false);
	player1body_6_Sprite:SetLifeTime(0.0);
	player1body_6_Sprite:SetVisible(true);
	player1body_6_Sprite:SetRotationAngle(0.0);
	player1body_6_Sprite:SetScale(1.0, 1.0);
	player1body_6_Sprite:SetCenter(Point2D(0.0,0.0));
	player1body_6_Sprite:SetZOrder(8.0);
	
	layer1_Layer:AddGameObject(player1body_6_Sprite)

	anim0 = SpriteAnimation(Game.Get():GetDirectory().."\\Resources\\Animations\\Hitbox.png",1,1,1.0);
	anim0:SetName("Hitbox");
	player1hitbox_14_Sprite = Player1(anim0);

	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		dynamicCollisionData =  DynamicObject();
		dynamicCollisionData:AddCollisionData(collisionActor3);
		dynamicCollisionData:SetCollisionType(false);
		dynamicCollisionData:SetCollisionThickness(2.0);
		dynamicCollisionData:SetBoundingRectangleCheckingTileMap(true);
		dynamicCollisionData:SetZCollision(0);
		dynamicCollisionData:SetCanCollid(0,true);
		dynamicCollisionData:SetCanCollid(2,true);
		dynamicCollisionData:SetUpdateOnIdle(true);
		player1hitbox_14_Sprite:AddCollision(dynamicCollisionData, layer1_Layer:GetCollisionId());
	end

	player1hitbox_14_Sprite:SetName("player1hitbox");
	player1hitbox_14_Sprite:SetCollisionActorIndex(3);
	player1hitbox_14_Sprite:SetOpacity(1.0);
	player1hitbox_14_Sprite:Play(true);
	player1hitbox_14_Sprite:SetPosition(Point2D(-200.0,-230.0));
	player1hitbox_14_Sprite:SetCurrentAnimationIndex(0);
	player1hitbox_14_Sprite:SetCurrentFrameIndex(0);
	player1hitbox_14_Sprite:SetLoop(true);
	player1hitbox_14_Sprite:SetAnimationSpeed(1.0);
	player1hitbox_14_Sprite:SetFlipHorizontal(false);
	player1hitbox_14_Sprite:SetFlipVertical(false);
	player1hitbox_14_Sprite:SetLifeTime(0.0);
	player1hitbox_14_Sprite:SetVisible(true);
	player1hitbox_14_Sprite:SetRotationAngle(0.0);
	player1hitbox_14_Sprite:SetScale(1.0, 1.0);
	player1hitbox_14_Sprite:SetCenter(Point2D(0.0,0.0));
	player1hitbox_14_Sprite:SetZOrder(10.0);
	
	if(not Game.Get():IsNetworkGame() or Game.Get():IsServer())
	then
		player1hitbox_14_Sprite:SetCenter(Point2D(0.0,0.0));
		player1hitbox_14_Sprite:AddPhysicalProperties(MassProperties(0.0,0.0,Point2D(0.0,0.0)),Physics.ODESolverMethodEuler);
		player1hitbox_14_Sprite:SetVelocity(Vector2D(0.0,0.0));
		player1hitbox_14_Sprite:SetAngularVelocity(0.0);
	end

	layer1_Layer:AddGameObject(player1hitbox_14_Sprite)



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
	level0_Level:SetName("Combat");
	level0_Level:SetClearBackBuffer(false);

	layer0_Layer = Layer(0.0);
	layer0_Layer:SetName("Combat_HUD");

	layer0_Layer:SetCollisionProperties(Point2D(-400,-300),800,600);
	layer1_Layer = Layer(0.0);
	layer1_Layer:SetName("layer1");
	layer1_Layer:SetScale(1.0,1.0);
	layer1_Layer:SetRotation(0.0);
	layer1_Layer:SetCollisionProperties(Point2D(-400,-300),800,600);

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
	if(levelName == "Combat")
	then
		return 0;
	else	end
	return -1;
end

function Reset()

	--Cameras
	camera0_2_Camera = 0;

	--Texts
	player1power_12_Text = 0;

	--Sounds

	--TileMaps

	--Sprites
	background_3_Sprite = 0;
	roundBullet_8_Sprite = 0;
	player2proxy_10_Sprite = 0;
	player1proxy_15_Sprite = 0;
	player1body_6_Sprite = 0;
	player1hitbox_14_Sprite = 0;

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
	player1hitbox_14_Sprite:Mount(player1body_6_Sprite);
	
end
