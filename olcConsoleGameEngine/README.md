Dans le fichier olcConsoleGameEngine.h, nous avons des variables 'protected'

protected:
	int m_nScreenWidth;
	int m_nScreenHeight;
	CHAR_INFO *m_bufScreen;
	std::wstring m_sAppName;
	HANDLE m_hOriginalConsole;
	CONSOLE_SCREEN_BUFFER_INFO m_OriginalConsoleInfo;

    /* on commence par deux HANDLE pour chaque console qui est par defaut les buffers(mémoire tampon qui stocke temporairement des données) de sortie 
	HANDLE m_hConsole;
	HANDLE m_hConsoleIn;
	SMALL_RECT m_rectWindow;

    /* il s'agit de deux pointeurs vers des tableaux qui vont stocker les états du clavier */
    /* ils vont être augmentés car parce qu'on va stocker 256 états différents et les tableaux seront initialisés dans le constructeur */
	short m_keyOldState[256] = { 0 };
	short m_keyNewState[256] = { 0 };

    /* on stocke également deux tableaux booléens pour les boutons de la souris */
	bool m_mouseOldState[5] = { 0 };
	bool m_mouseNewState[5] = { 0 };

	bool m_bConsoleInFocus = true;	
	bool m_bEnableSound = false;

	// These need to be static because of the OnDestroy call the OS may make. The OS
	// spawns a special thread just for that
	static std::atomic<bool> m_bAtomActive;
	static std::condition_variable m_cvGameFinished;
	static std::mutex m_muxGame;
};
