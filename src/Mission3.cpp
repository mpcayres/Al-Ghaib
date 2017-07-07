#include "Mission3.hpp"
#include "PickUpObject.hpp"
#include "StealthObject.hpp"
#include "SceneDoor.hpp"
#include "MissionManager.hpp"
#include "Geometry.hpp"

 Music Mission3::music;

Mission3::Mission3() : Mission(), paradoUrso(false),paradoGato(false), endMission(false) {
	initialState = "LivingRoomState"; // trocar para comeÃ§ar da sala?
	initialX = 230; initialY = 400;
	MissionManager::missionManager->SetPos(initialX, initialY);
	MissionManager::player->SetDirecao((int) Player::NORTE);
	MissionManager::missionManager->randomStates = true;
	atraidoNovelo = 0;
	atraidoTV = 0;

	MissionManager::enemy->ChangeClothes(1);

	meowcount = 0;
	momcount = 0;
	countBear = 0;
	countCat = 0;
	//bronca = false;

	SDL_Color redwine = SDL_Color();
	redwine.r = 102;
	redwine.g = 0;
	redwine.b = 0;

	SDL_Color white = SDL_Color();
	white.r = 255;
	white.g = 255;
	white.b = 255;

	tx = Text("font/uwch.ttf", 50, Text::TextStyle::BLENDED, "MISSÃO 3", redwine, 0, 0);
	tx.SetPos(0, 0, true, true);
	creepy = Text("font/uwch.ttf", 30, Text::TextStyle::BLENDED, "  ", redwine, 0, 0);
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

	miado = Timer();
}

Mission3::~Mission3() {

}

void  Mission3::Pause(){ }

void  Mission3::Resume(){ }

void Mission3::Update(float dt){

	InputManager instance = InputManager::GetInstance();
	bool trancada = false;
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
	time.Update(dt);
	cooldown.Update(dt);

	if(gameOver){
		if(time.Get() > 3){
			Game::GetInstance().GetCurrentState().ChangeMission(3);
		}
	}
	if(endMission && drink){
		Game::GetInstance().GetCurrentState().ChangeMission(4);
	}
	//TROCAR PARA SALA DE ESTAR COMO COMODO INICIAL ////////////////////////////////////////////////////////////////////
	if(MissionManager::missionManager->IsState("LivingRoomState") &&
			MissionManager::missionManager->countLivingRoomState <= 1){
		MissionManager::enemy->show = true;


			momcount ++;

		if(momcount == 1 ){
			MissionManager::enemy->SetPosition(700, 190);

			MissionManager::enemy->SetDestinationPath(Vec2(220, 165));
			MissionManager::enemy->SetDestinationPath(Vec2(220, 190));
			MissionManager::enemy->SetDestinationPath(Vec2(620, 190));
			MissionManager::enemy->SetDestinationPath(Vec2(660, 190));
			MissionManager::enemy->SetDestinationPath(Vec2(620, 190));
			MissionManager::enemy->SetDestinationPath(Vec2(730, 190));
			MissionManager::enemy->SetDestinationPath(Vec2(620, 190));
			MissionManager::enemy->SetDestinationPath(Vec2(730, 190));
			MissionManager::enemy->SetDestinationPath(Vec2(620, 190));
			MissionManager::enemy->SetDestinationPath(Vec2(730, 190));
			MissionManager::enemy->SetDestinationPath(Vec2(620, 190));
			MissionManager::enemy->SetDestinationPath(Vec2(730, 190));
		}

		MissionManager::player->SetBlocked(true);
		if(flagTimer == true && time.Get() > 3){
			tx.SetText(" ");
			showBox = false;
			creepy.SetText(" ");
			ImageProfileBox (6);
			flagTimer = false;
		}

		if(time.Get() > 5){

			Sound sussurro = Sound ("audio/ghostly-whispers.wav");
			if(somWhispers == false){
				sussurro.Play(0);
				somWhispers = true;
			}
			ImageProfileBox (4); //BOTA URSO
			falas.SetText("OLHA ESSA QUE CHAMAS DE MÃE");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = 5;
			showBox = true;
		}
		if(time.Get() > 10){
			falas.SetText("O QUE É ESSA ROUPA?");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = 10;
			showBox = true;
		}
		if(time.Get() > 15 && trancada == false && cooldown.Get() > 3){
			falas.SetText("AINDA É REALMENTE ELA POR BAIXO DESSE PANO NEGRO?");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = 15;
			showBox = true;

		}
		if(time.Get() > 20 && trancada == false && cooldown.Get() > 3){
			falas.SetText("TEMOS QUE INVESTIGAR ISSO");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = 20;
			showBox = true;
			MissionManager::player->SetBlocked(false);
			MissionManager::enemy->show = false;
		}
		if(time.Get() > 25 && trancada == false && cooldown.Get() > 3){
			falas.SetText(" ");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = 25;
			showBox = false;
			MissionManager::enemy->show = false;
		}
			MessageDoor(dt);
			//TROCANDO DE COMODO. ENTRANDO NO CORREDOR PELA PRIMEIRA VEZ
	}

	if(MissionManager::missionManager->IsState("HallState")){
			MissionManager::player->SetBlocked(false);
		//HallState++;
		std::cout << MissionManager::missionManager->countHallState << std::endl;
		std::cout << "HallState" << std::endl;
		if(state != MissionManager::missionManager->changeState){
			state = MissionManager::missionManager->changeState;
			//MissionManager::missionManager->player->box.x = 510;
			//MissionManager::missionManager->player->box.y = 200;
			MissionManager::enemy->show = false;
			MissionManager::enemy->SetPosition(975,115);
			time.Restart();
		}
		if(time.Get() < 3 && trancada == false && cooldown.Get() > 3){
			falas.SetText(" ");
			falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
			ultimoTempo = 3;
			showBox = false;
		}


		if(MissionManager::cat->attractedTV){
			MissionManager::cat->show = false;
		}else{
			MissionManager::cat->show = true;
		}
		countCat++;
		//if(count == 1){
		int dist = MissionManager::cat->box.DistanceRect(MissionManager::player->box);
		std::cout << "dist" << dist << std::endl;


		if(countCat == 1  && atraidoNovelo == 0){
			MissionManager::cat->SetDestinationPath(Vec2(1000, 200));
			MissionManager::cat->SetDestinationPath(Vec2(900, 200));
			MissionManager::cat->SetDestinationPath(Vec2(1000, 200));
			MissionManager::cat->SetDestinationPath(Vec2(890, 200)); //4Âº DESTINO
			MissionManager::cat->SetDestinationPath(Vec2(970, 200)); //3Âº DESTINO
			MissionManager::cat->SetDestinationPath(Vec2(1000, 200)); //2Âº DESTINO
			MissionManager::cat->SetDestinationPath(Vec2(900, 200)); //1Âº DESTINO
					//paradoGato = true;
		}
		if(time.Get()>5  && atraidoNovelo == 0){
			MissionManager::cat->SetDestinationPath(Vec2(890, 200));
		}
		if( dist < 250 && atraidoNovelo == 0){
			MissionManager::cat->SetDestinationPath(Vec2(980, 200));
		}
		/*if(MissionManager::cat->attractedWool == false && dist > 200){
			MissionManager::cat->SetDestinationPath(Vec2(1000, 200));
			MissionManager::cat->SetDestinationPath(Vec2(900, 200));
		}*/

		if(dist < 100 && MissionManager::cat->show == true){
			Sound meow1 = Sound ("audio/cat-meow-1.wav");
			Sound meow2 = Sound ("audio/cat-meow-2.wav");
			Sound meow3 = Sound ("audio/cat-meow-3.wav");
			if(miado.Get() > 3){
				somGato = false;
				miado.Restart();
			}else{
				miado.Update(dt);
			}
			if(somGato == false){
				MissionManager::player->AddRuido(35);
				if(meowcount == 0)
					meow1.Play(0);
				else if(meowcount == 1)
					meow2.Play(0);
				else if(meowcount == 2){
					meow3.Play(0);
					meowcount = -1;
				}
				somGato = true;
				meowcount++;
			}
		}

		if(MissionManager::cat->attractedWool == true && MissionManager::cat->attractedTV == false){
			atraidoNovelo++;
			if(atraidoNovelo == 1){
				MissionManager::cat->PathFlush();
				MissionManager::cat->SetDestinationPath(Vec2(1350, 450));
				MissionManager::cat->SetDestinationPath(Vec2(980, 450));
				MissionManager::cat->SetDestinationPath(Vec2(980, 300));
				contador =  MissionManager::missionManager->countHallState;
			}
			else if (atraidoNovelo > 30){
				MissionManager::cat->SetDestinationPath(Vec2(1350, 450));
			}

		}else if(MissionManager::cat->attractedWool == true && MissionManager::cat->attractedTV == true){
			MissionManager::cat->attractedWool = false;
		}

		if(time.Get() > 7 && time.Get() < 7.5 && trancada == false && cooldown.Get() > 3){
			Sound portaDestrancando = Sound ("audio/meow-sample.wav");
			portaDestrancando.Play(0);
		}
		if (MissionManager::player->GetRuido()>70 ){
			MissionManager::enemy->show = true;
			SceneDoor::count = ABRE;
			momcount ++;
			std::cout << "momcount" << momcount << std::endl;
			if(MissionManager::enemy->show){
				if(momcount == 1){

					SceneDoor::ValorPassar = 15;
					ImageProfileBox(2);
					falas.SetText("O QUE JÃ FALEI SOBRE SAIR DA CAMA?");
					falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
					ultimoTempo = (int)time.Get();
					showBox = true;
				}
			}
			if(MissionManager::enemy->show && time.Get() > ultimoTempo + 2){
				SceneDoor::ValorPassar = 0;
			}
			if(MissionManager::enemy->show && time.Get() > ultimoTempo + 4){

				falas.SetText(" ");
				ImageProfileBox (6);
				falas.SetPos(0, Game::GetInstance().GetHeight()-POSY_FALA, true, false);
				ultimoTempo = ultimoTempo + 4;
				showBox = false;
			}
		}


	} if(MissionManager::missionManager->IsState("LivingRoomState") &&
				MissionManager::missionManager->countLivingRoomState > 1){
		MissionManager::cat->show = false;
		MissionManager::enemy->show = false;
		if(state != MissionManager::missionManager->changeState){
			state = MissionManager::missionManager->changeState;
			//MissionManager::missionManager->player->box.x = 400;
			//MissionManager::missionManager->player->box.y = 400;
			MissionManager::enemy->SetPosition(400,400);
			time.Restart();
		}

		if(MissionManager::cat->attractedTV == true && MissionManager::cat->attractedWool == false){
			MissionManager::cat->show = true;
			atraidoTV++;

			contador =  MissionManager::missionManager->countLivingRoomState;
			if(atraidoTV == 1){
				MissionManager::cat->PathFlush();
				MissionManager::cat->SetPosition(230, 300);
				//MissionManager::missionManager->cat->box.x = 400;
				//MissionManager::missionManager->cat->box.y = 400;
				time.Restart();

				MissionManager::cat->SetDestinationPath(Vec2(610, 450));
				MissionManager::cat->SetDestinationPath(Vec2(500, 450));
				MissionManager::cat->SetDestinationPath(Vec2(400, 430));
				MissionManager::cat->SetDestinationPath(Vec2(400, 350));
				MissionManager::cat->SetDestinationPath(Vec2(230, 350));
			}
			else if (time.Get()>5){
				MissionManager::cat->SetDestinationPath(Vec2(610, 450));
			}
		}


	}if(MissionManager::missionManager->IsState("MomRoomState")){

		MissionManager::enemy->show = false;
		if(state != MissionManager::missionManager->changeState){
			state = MissionManager::missionManager->changeState;
			//MissionManager::missionManager->player->box.x = 400;
			//MissionManager::missionManager->player->box.y = 400;
			MissionManager::enemy->SetPosition(225, 190);
			MissionManager::enemy->Reset();
			time.Restart();
		}
		Vec2 *covil = new Vec2(570, 470);
		float dist = 0;

		dist = covil->Distance(Vec2(MissionManager::player->box.x, MissionManager::player->box.y));
		if(dist<120){
			bronca = true;
			SceneDoor::count = ABRE;
			SceneDoor::ValorPassar = 4;
			MissionManager::player->SetBlocked(true);
			MissionManager::enemy->show = true;


			momcount2 ++;
			if(time.Get() < 17){
				SetPiscaPisca(20, 0.4);

			}
			if(momcount2 == 1 ){

				time.Restart();
				MissionManager::enemy->SetDestinationPath(Vec2(225, 190));
			}
			if(time.Get() > 2 && time.Get() < 6){

				showBox = true;
				ImageProfileBox (2);
				falas.SetText("O QUE ESTÁ FAZENDO AQUI?");
				falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
			}
			if(time.Get() > 6 && time.Get() < 10){
				showBox = true;
				ImageProfileBox (2);
				falas.SetText("NÃO TOLERAREI ISSO!");
				falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
			}
			if(time.Get() > 10 && time.Get() < 14){
				showBox = true;
				ImageProfileBox (2);
				falas.SetText("JÁ PARA O QUARTO!");
				falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
			}
			if(time.Get() > 14 && time.Get() < 18){
				showBox = true;
				ImageProfileBox (2);
				falas.SetText("DEIXEI SEU LEITE LÁ!");
				falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
			}
			if(time.Get() > 18){
				showBox = false;
				ImageProfileBox (6);
				falas.SetText(" ");
				falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
			}
			if(time.Get() > 19)
				Game::GetInstance().GetCurrentState().ChangeState("MomRoomStage","StageState");
		}
	}
	if(MissionManager::missionManager->IsState("StageState") /*&& bronca*/){
		std::cout << "entrei!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
		if(state != MissionManager::missionManager->changeState){
			std::cout << time.Get() << std::endl;
				MissionManager::player->SetPosition(805, 260);
				state = MissionManager::missionManager->changeState;
				MissionManager::enemy->show = false;
				time.Restart();
		}
		if(time.Get() > 8 && time.Get() < 12){
				showBox = true;
				ImageProfileBox (4);
				falas.SetText("U: É MELHOR BEBER SEU LEITE");
				falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		}
		if(time.Get() > 12){
			showBox = false;
			ImageProfileBox (6);
			falas.SetText(" ");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		}

		if(time.Get() > 40 && time.Get() < 44){
			showBox = true;
			ImageProfileBox (4);
			falas.SetText("BEBAAAAAAAAAAAAAAAA");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		}
		if(time.Get() > 44){
			showBox = false;
			ImageProfileBox (6);
			falas.SetText(" ");
			falas.SetPos(0, Game::GetInstance().GetHeight()-50, true, false);
		}
		Vec2 *leite = new Vec2(255, 405);
		float dist = 0;

		dist = leite->Distance(Vec2(MissionManager::player->box.x, MissionManager::player->box.y));
		if(dist<80 && InputManager::GetInstance().KeyPress(Z_KEY)){
			drink = true;
			endMission = true;
		}


	}

	if(time.Get() >= 4 && fadeIn){
		UpdateVariable(dt, 80);
	}

	if(time.Get() >= 6){
		//PiscaPisca(dt, 6, 0.6);
	}
	PiscaPisca(dt);
}

void Mission3::Render(){
	if(time.Get() < 4 && fadeIn){
		blackSquare.Render(0, 0, 0);
		tx.Render(0,0);
		creepy.Render(0,0);
	} else if((time.Get() >= 4 && fadeIn) || !bloqBlack){
		spFade.Render(0,0,0);
	}

	if((((MissionManager::missionManager->IsState("LivingRoomState") && MissionManager::missionManager->countLivingRoomState <= 1 && time.Get() > 4) ||
		((MissionManager::missionManager->IsState("LivingRoomState") && MissionManager::missionManager->countLivingRoomState > 1) ||
			MissionManager::missionManager->IsState("HallState"))) && !MissionManager::player->GetBloqHUD()) || 	MissionManager::missionManager->IsState("MomRoomState")){
		if(showBox){
			falasBox.Render(falasBoxRect.x /*- Camera::pos.x*/, falasBoxRect.y /*- Camera::pos.y*/, 0);
			profileBox.Render(profileBoxX, profileBoxY, 0);
		}
		falas.Render(0,0);
	}
}

void Mission3::SetObjectStage(){
	SceneDoor* Door = new SceneDoor(800, 200, "HallState");
	objectStage.emplace_back(Door);

	StealthObject* Armario2 = new StealthObject(1400, 110, "img/cenario/geral/armario-corredor-fechado.png");
	objectStage.emplace_back(Armario2);

	SceneObject* Bau = new SceneObject(300, 490,  "img/cenario/geral/bau-fechado.png",
			"img/cenario/geral/bau-aberto.png", 0, 1, 1, "", SceneObject::SAMEY_UP);
	objectStage.emplace_back(Bau);

	MovingObject* Cadeira = new MovingObject(730, 300, "img/cenario/geral/cadeira.png");
	objectStage.emplace_back(Cadeira);

	PickUpObject* Copo = new PickUpObject(255, 405, "img/inventario/copo-cheio.png", "img/inventario/copo-cheio.png", false, 0.5, 0.5, true);
	objectStage.emplace_back(Copo);

}

void Mission3::SetObjectHall(){
	SceneDoor* DoorToMomRoom = new SceneDoor(970, 105, "MomRoomState", true,
			"img/cenario/geral/door-closed.png", "img/cenario/geral/door-opened.png", 0);
	objectHall.emplace_back(DoorToMomRoom);

	SceneObject* CriadoMudo = new SceneObject(100, 160,
			"img/cenario/filho/criado-fechado.png", "img/cenario/filho/criado-aberto.png");
	objectHall.emplace_back(CriadoMudo);

	MovingObject* Vase = new MovingObject(1000, 450, "img/cenario/geral/vaso.png");
	objectHall.emplace_back(Vase);

	SceneObject* Apple = new SceneObject(350, 330, "img/cenario/geral/maca.png", "img/cenario/geral/maca.png", 0, 0.3, 0.3);
	objectHall.emplace_back(Apple);

	SceneObject* CaixaDeAreia = new SceneObject(1400, 450,
			"img/cenario/corredor/caixa-areia.png", "img/cenario/corredor/caixa-novelo.png", 0, 1, 1, "", 3, true);
	objectHall.emplace_back(CaixaDeAreia);


}

void Mission3::SetObjectLivingRoom(){
	MovingObject* Banco1 = new MovingObject(510, 470, "img/cenario/sala/banquinho.png", true);
	objectLivingRoom.emplace_back(Banco1);

	MovingObject* Banco2 = new MovingObject(570, 470, "img/cenario/sala/banquinho.png", true);
	objectLivingRoom.emplace_back(Banco2);
}

void Mission3::SetObjectMomRoom(){

}
