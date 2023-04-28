#include <DxLib.h>
#include"object.h"
#include"config.h"

void LoadInit() {
	SetOutApplicationLogValidFlag(LOGSET_MODE);//ログの書き出し設定
	ChangeWindowMode(WINDOW_MODE);	//ウィンドウモードにする
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);	//ウィンドウサイズを設定する
	SetWindowSizeExtendRate(WINDOW_EXTEND);//ウィンドウ拡大率
	//SetWindowSizeChangeEnableFlag(TRUE);//途中大きさ変更あり
	SetWindowStyleMode(WINDOW_STYLE);//ウィンドウの最大化ボタンを機能させる。
	SetDrawScreen(DX_SCREEN_BACK);	//裏画面を描画対象へ
	//SetUseIMEFlag(true);// ＩＭＥを使用するかどうかを設定する
	SetWindowText(WINDOW_NAME);

}

//プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	LoadInit();
	
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

		
	//SetAlwaysRunFlag(TRUE);//ウィンドウがアクティブではない状態でも動く
	//SetUseZBuffer3D(TRUE);
	//SetWriteZBuffer3D(TRUE);
		

	//最初に１回呼ぶ
	Init();

	//メイン処理
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		clsDx();
		ClearDrawScreen();	//裏画面の描画を全て消去
		Update();
		Draw();
		ScreenFlip();		//裏画面と表画面の入替
	}
	Delete();

	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
