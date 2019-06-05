#pragma once
#include <Windows.h>
#include "Graphic.h"
#include "Keyboard.h"
#include "Scene.h"

class Game
{
private:
	HINSTANCE hInstance;	//HINSTANCE của chương trình 
	HWND hWnd;				//HWND của của sổ
	int width;				//Chiều rộng cửa sổ
	int height;				//Chiều cao cửa sổ
	char windowName[256];	//Tên cửa sổ
	int fps;				//frame per second

	//Hàm xử lý cửa sổ
	static HRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	Graphic* graphic;		//Khai báo đối tượng graphic
	
	Keyboard* keyboard;		//Khai báo đối tượng Keyboard

	Scene* SceneManager;

public:
	Game(HINSTANCE hInstance, int width, int height, char* name, int fps);
	~Game();

	
	bool InitWindow();

	bool InitGraphic();

	
	void InitKeyboard();

	
	void InitScene();

	
	void Init();

	
	void Run();

	
	void Update(float dt);

	
	void Render();
};

