Dans le fichier olcConsoleGameEngine.h, nous avons des variables 'protected'

// variable 'protected' (accessibles dans la classe qui les définit et dans les classes qui héritent de cette classe.)
protected:
    // variable qui determine la largeur de l'ecran
	int m_nScreenWidth;
    // variable qui determine la hauteur de l'ecran
	int m_nScreenHeight;
    // CHAR_INFO qui se decompose (soit en Glyphes (CHARS) soit en Palette(couleur 1er / arrière plan))
	CHAR_INFO *m_bufScreen;
    // wchar pour le nom de l'app
	std::wstring m_sAppName;

    // on stocke certaines infos qui sont utilisées pour remettre la console dans son etat d'origine en cas d'erreur
	HANDLE m_hOriginalConsole;
	CONSOLE_SCREEN_BUFFER_INFO m_OriginalConsoleInfo;

    // on commence par deux HANDLE pour chaque console qui est par defaut les buffers
    (mémoire tampon qui stocke temporairement des données) de sortie et chaque console pour les buffers d'entrée.
	HANDLE m_hConsole;   //buffer de sortie
	HANDLE m_hConsoleIn; //buffer d'entree : permet de generer les evenements clavier / souris
	SMALL_RECT m_rectWindow;

    // il s'agit de deux pointeurs vers des tableaux qui vont stocker les états du clavier 
    // ils vont être augmentés car parce qu'on va stocker 256 états différents et les tableaux seront initialisés dans le constructeur 
	short m_keyOldState[256] = {0};
	short m_keyNewState[256] = {0};

    // on stocke également deux tableaux booléens pour les boutons de la souris 
	bool m_mouseOldState[5] = {0};
	bool m_mouseNewState[5] = {0};

	bool m_bConsoleInFocus = true;	
	bool m_bEnableSound = false;

	// These need to be static because of the OnDestroy call the OS may make. The OS
	// spawns a special thread just for that
	static std::atomic<bool> m_bAtomActive;
	static std::condition_variable m_cvGameFinished;
	static std::mutex m_muxGame;
};

Nous avons également le constructeur

// on determine la classe
class olcConsoleGameEngine
{
public:
	olcConsoleGameEngine()
	{
        // le constructeur définit par defaut une largeur de 80px et une hauteur de 30px : c'est assez petit
		m_nScreenWidth = 80;
		m_nScreenHeight = 30;

        // HANDLEs de l'entrée standard et de la sortie standard afin de pouvoir communiquer avec la console
		m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		m_hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
        
        // copie la valeur 'static_cast<unsigned char>(ch)' dans chacun des premiers caractère 'count'
        // de l'objet pointé par dest.(m_keyNewState / m_keyOldState / m_keys)
        // creation de deux tableaux pour stocker le clavier (fonctionne en stokant ancien / nouvel etat)
        // et en recherchant les différences entre eux par image qui permettent de declencher des events
        // par defaut, tous les etats du clavier sont à 0
		std::memset(m_keyNewState, 0, 256 * sizeof(short));
		std::memset(m_keyOldState, 0, 256 * sizeof(short));
		std::memset(m_keys, 0, 256 * sizeof(sKeyState));
        // position en X de la souris
		m_mousePosX = 0;
        // position en Y de la souris
		m_mousePosY = 0;

        // son non disponible par defaut
		m_bEnableSound = false;
        // nom de l'app par defaut
		m_sAppName = L"Default";
	}

ConstructConsole concerne beaucoup d'appels au SDK de Windows


// methode qui prend en paramètres : (largeur, hauteur, police de la largeur, police de la hauteur)
int ConstructConsole(int width, int height, int fontw, int fonth)
	{
		if (m_hConsole == INVALID_HANDLE_VALUE)
			return Error(L"Bad Handle");
        
        // largeur de l'ecran
		m_nScreenWidth = width;
        // hauteur de l'ecran
		m_nScreenHeight = height;

		// Modifiez la taille visuelle de la console au minimum afin que le tampon d'écran (screen buffer)
        // puisse rétrécir en dessous de la taille visuelle réelle
		m_rectWindow = { 0, 0, 1, 1 };
		SetConsoleWindowInfo(m_hConsole, TRUE, &m_rectWindow);

		// Definit la taille du tampon de l'ecran(screen buffer)
		COORD coord = { (short)m_nScreenWidth, (short)m_nScreenHeight };
		if (!SetConsoleScreenBufferSize(m_hConsole, coord))
			Error(L"SetConsoleScreenBufferSize");

		// Assigne le tampon de l'ecran(screen buffer) à la console
		if (!SetConsoleActiveScreenBuffer(m_hConsole))
			return Error(L"SetConsoleActiveScreenBuffer");
		
		// Définissez la taille de la police maintenant que le tampon d'écran a été attribué à la console
        // Necessaire pour obtenir la plus grande taille possible de fenetre de la console
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = fontw;
		cfi.dwFontSize.Y = fonth;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;

	/*	DWORD version = GetVersion();
		DWORD major = (DWORD)(LOBYTE(LOWORD(version)));
		DWORD minor = (DWORD)(HIBYTE(LOWORD(version)));*/

		//if ((major > 6) || ((major == 6) && (minor >= 2) && (minor < 4)))		
		//	wcscpy_s(cfi.FaceName, L"Raster"); // Windows 8 :(
		//else
		//	wcscpy_s(cfi.FaceName, L"Lucida Console"); // Everything else :P

		//wcscpy_s(cfi.FaceName, L"Liberation Mono");
		wcscpy_s(cfi.FaceName, L"Consolas");
		if (!SetCurrentConsoleFontEx(m_hConsole, false, &cfi))
			return Error(L"SetCurrentConsoleFontEx");
