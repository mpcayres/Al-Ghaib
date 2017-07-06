#include "Mission4.hpp"
#include "PickUpObject.hpp"
#include "StealthObject.hpp"
#include "SceneDoor.hpp"
#include "MissionManager.hpp"
#include "Animation.hpp"

 Music Mission4::music;

Mission4::Mission4() : Mission(), paradoUrso(false),paradoGato(false) {
	initialState = "StageState";
	initialX = 300; initialY = 300;
	MissionManager::missionManager->SetPos(initialX, initialY);
	MissionManager::missionManager->randomStates = true;

	meowcount = 0;
	momcount = 0;
	countBear = 0;
	countCat = 0;

	creepyEffect = Timer();
	contCreepy = 0;

	MissionManager::player->drogado = true;

	SDL_Color redwine = SDL_Color();
	redwine.r = 102;
	redwine.g = 0;
	redwine.b = 0;

	SDL_Color white = SDL_Color();
	white.r = 255;
	white.g = 255;
	white.b = 255;

	tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "MISSÃO 4", redwine, 0, 0);
	tx.SetPos(0, 0, true, true);
	creepy = Text("font/uwch.ttf", 30, Text::TextStyle::BLENDED, " ", redwine, 0, 0);
	creepy.SetPos(0, Game::GetInstance().GetHeight()-120, true, false);

	falas = Text("font/AA_typewriter.ttf", 25, Text::TextStyle::BLENDED , " ", white, 0, 0);
	falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
	showBox = false;
	//ultimoTempo = 3;
	/*intro = Music("audio/menu-intro.wav");
	music = Music("audio/menu-loop.wav");
	intro.Play(1);
	Mix_HookMusicFinished(&TitleState::LinkMusic);*/

	//Sound intro("audio/boom.wav");
	//intro.Play(1);

	SetObjectStage();
	SetObjectHall();
	SetObjectLivingRoom();

	MissionManager::cat->SetPosition(1000, 200);
}

Mission4::~Mission4() {

}

void  Mission4::Pause(){ }

void  Mission4::Resume(){ }

void Mission4::Update(float dt){

	InputManager instance = InputManager::GetInstance();
	//bool trancada = false;
	if(instance.KeyPress(ESCAPE_KEY)){
		popRequested = true;
	}
	//quitRequested = instance.QuitRequested();
	if(instance.KeyPress(SPACE_KEY)){
		std::cout << "SPACE KEY PRESSED" << std::endl;
		if(time.Get() < 3){
			time.Set(3);
		}
		bloqBlack = true;
		fadeIn = false;
		alpha = TRANSPARENT;
		if (spFade.IsOpen()) {
			spFade.ChangeAlpha(alpha);
		}
	}
	if(time.Get()<100)
			time.Update(dt);
	cooldown.Update(dt);
	if(!fadeIn) creepyEffect.Update(dt);

	if(endMission && time.Get()> 10 && first == 1){
		Game::GetInstance().GetCurrentState().ChangeMission(5);
	}
	//URSO APARECE BATENDO NA PORTA. BOTAR SOM DE PORTA TENTANDO ABRIR ANTES DE ELE FALAR
	if(MissionManager::missionManager->IsState("StageState") &&
			MissionManager::missionManager->countStageState <= 1){
			if(time.Get() > 5 && trancada == false && cooldown.Get() > 3){
				ImageProfileBox(4);
				falas.SetText("U:TEMOS QUE VOLTAR AO QUARTO");
				falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
				ultimoTempo = 15;
				showBox = true;

			}
			if(time.Get() > 10 && trancada == false && cooldown.Get() > 3){
				falas.SetText("U: CERTEZA QUE DEVE TER ALGO NAQUELE PORÃO");
				falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
				ultimoTempo = 20;
				showBox = true;
				MissionManager::player->SetBlocked(false);
				MissionManager::enemy->show = false;
			}
			if(time.Get() > 15 && trancada == false && cooldown.Get() > 3){
				falas.SetText(" ");
				ImageProfileBox(6);
				falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
				ultimoTempo = 25;
				showBox = false;
				MissionManager::enemy->show = false;
			}


			MessageDoor(dt);
			//TROCANDO DE COMODO. ENTRANDO NO CORREDOR PELA PRIMEIRA VEZ
	}else if(MissionManager::missionManager->IsState("HallState") &&
							MissionManager::missionManager->countHallState <= 1){

		if(state != MissionManager::missionManager->changeState){
				state = MissionManager::missionManager->changeState;
				time.Restart();
		}


		MessageDoor(dt);

	}else if(MissionManager::missionManager->IsState("MomRoomState")){

			if(state != MissionManager::missionManager->changeState){
				state = MissionManager::missionManager->changeState;
				time.Restart();
			}

			Vec2 *covil = new Vec2(570, 470);
			float dist = 0;

			dist = covil->Distance(Vec2(MissionManager::player->box.x, MissionManager::player->box.y));
			if(dist<100 && InputManager::GetInstance().KeyPress(Z_KEY)){
				//Camera::ZoomCreepy(5, true);
				first++;
				std::cout << time.Get() << " e " << first << std::endl;
				if(first == 1)
					time.Restart();

			}
			else{

				SetPiscaPisca(20, 0.4);
				PiscaPisca(dt);

			}
			if(first == 1 && time.Get()>1){
				ImageProfileBox (4);
				falas.SetText("I-ISSO QUE ELA TA COMENDO... É O GATO?");
				falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
				showBox = true;


				Game::GetInstance().GetCurrentState().AddObject(
				new Animation(350, 200, 0,
					"img/sprite/mom-comendo-gato.png", 5, 0.3, false, 7 ,  7, true));
				first++;
				endMission = true;

			}

	}

	if(time.Get() >= 4 && fadeIn){
		UpdateVariable(dt, 80);
	}

	if(!fadeIn && (creepyEffect.Get() > 3) && (contCreepy == 0)&&(!MissionManager::missionManager->IsState("MomRoomState"))){
		creepyEffect.Restart();
		contCreepy = 1;
		//std::cout << "piscapisca" << std::endl;
		SetPiscaPisca(4, 0.4);
		//std::cout << "oi" << std::endl;
	}

	if(!fadeIn && (creepyEffect.Get() > 8) && (contCreepy == 1)&&(!MissionManager::missionManager->IsState("MomRoomState"))){
		creepyEffect.Restart();
		contCreepy = 2;
		Camera::ZoomCreepy(1, true);
		SetPiscaPisca(6, 0.4);
		//std::cout << "oi" << std::endl;
	}

	if(!fadeIn && (creepyEffect.Get() > 2) && (contCreepy == 2) &&(!MissionManager::missionManager->IsState("MomRoomState"))){
		creepyEffect.Restart();
		contCreepy = 0;
		Camera::ZoomCreepy(1, false);
		//std::cout << "oi" << std::endl;
	}

	PiscaPisca(dt);
}

void Mission4::Render(){
	if(time.Get() < 4 && fadeIn){
		blackSquare.Render(0, 0, 0);
		tx.Render(0,0);
		creepy.Render(0,0);
	} else if((time.Get() >= 4 && fadeIn) || !bloqBlack){
		spFade.Render(0,0,0);
	}

	if(((MissionManager::missionManager->IsState("StageState") && MissionManager::missionManager->countStageState <= 1 && time.Get() > 4) ||
		((MissionManager::missionManager->IsState("StageState") && MissionManager::missionManager->countStageState > 1) ||
			MissionManager::missionManager->IsState("HallState") || 	MissionManager::missionManager->IsState("MomRoomState"))) &&
		!MissionManager::player->GetBloqHUD()){
		if(showBox){
			falasBox.Render(falasBoxRect.x /*- Camera::pos.x*/, falasBoxRect.y /*- Camera::pos.y*/, 0);
			profileBox.Render(profileBoxX, profileBoxY, 0);
		}
		falas.Render(0,0);
	}
}

void Mission4::SetObjectStage(){
	SceneDoor* Door = new SceneDoor(800, 200, "HallState", false);
	objectStage.emplace_back(Door);

	SceneObject* Bau = new SceneObject(300, 490, "img/cenario/geral/bau-fechado.png",
			"img/cenario/geral/bau-aberto.png", 0, 1, 1, "", SceneObject::SAMEY_UP);
	objectStage.emplace_back(Bau);

	SceneObject* Copo = new SceneObject(550, 280, "img/inventario/copo-cheio.png", "", 0, 0.3, 0.3);
	objectStage.emplace_back(Copo);

	SceneObject* BrokenClown = new SceneObject(400, 500, "img/inventario/palhaco-quebrado.png", "", 0, 0.3, 0.3);
	objectStage.emplace_back(BrokenClown);

	MovingObject* Cadeira = new MovingObject(200, 470, "img/cenario/geral/cadeira.png");
	objectStage.emplace_back(Cadeira);
}

void Mission4::SetObjectHall(){
	SceneObject* CriadoMudo = new SceneObject(100, 160,
			"img/cenario/filho/criado-fechado.png", "img/cenario/filho/criado-aberto.png");
	objectHall.emplace_back(CriadoMudo);


	SceneDoor* DoorToMomRoom = new SceneDoor(970, 105, "MomRoomState", true,
			"img/cenario/geral/door-closed.png", "img/cenario/geral/door-opened.png", 1);
	objectHall.emplace_back(DoorToMomRoom);

	SceneObject* Bau = new SceneObject(1000, 490,  "img/cenario/geral/bau-fechado.png",
			"img/cenario/geral/bau-aberto.png", 0, 1, 1, "InventoryKey", SceneObject::SAMEY_UP);
	objectHall.emplace_back(Bau);

	MovingObject* Vase = new MovingObject(1300, 450, "img/cenario/geral/vaso.png");
	objectHall.emplace_back(Vase);

	SceneObject* PoteRacao = new SceneObject(180, 490,
			"img/cenario/corredor/pote-com-racao.png", "img/cenario/corredor/pote-com-racao.png");
	objectHall.emplace_back(PoteRacao);
	SceneObject* PoteAgua = new SceneObject(120, 490,
			"img/cenario/corredor/pote-sem-racao.png", "img/cenario/corredor/pote-sem-racao.png");
	objectHall.emplace_back(PoteAgua);
}

void Mission4::SetObjectLivingRoom(){

}

void Mission4::SetObjectMomRoom(){

}
