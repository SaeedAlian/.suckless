/* See LICENSE file for copyright and license details. */

/* consts */
#define SCRIPTSDIR "$HOME/.suckless/scripts/.local/bin"

/* defaults */
#define VPN "hiddify"
#define TERMINAL "st"
#define BROWSER "librewolf"
#define GUIFM "pcmanfm-qt"
#define CALCULATOR "qalculate-qt"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=9:antialias=true" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=9:antialias=true";
static const char bg1[]       = "#000000";
static const char bg2[]       = "#5080c0";
static const char fg1[]       = "#fefefe";
static const char fg2[]       = "#fefefe";
static const char border1[]       = "#444444";
static const char border2[]       = "#5080c0";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { fg1,       bg1,       border1},
	[SchemeSel]  = { fg2,       bg2,       border2},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "0" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                  instance          title     tags mask     isfloating   monitor */
	{ "Brave-browser",        NULL,             NULL,     1 << 1,       0,           -1       },
	{ "LibreWolf",            NULL,             NULL,     1 << 1,       0,           -1       },
	{ "Chromium-browser",     NULL,             NULL,     1 << 1,       0,           -1       },
	{ "firefox",              NULL,             NULL,     1 << 1,       0,           -1       },
	{ "discord",              NULL,             NULL,     1 << 3,       0,           -1       },
	{ "nekoray",              NULL,             NULL,     1 << 4,       0,           -1       },
	{ "Hiddify",              NULL,             NULL,     1 << 4,       0,           -1       },
	{ "Clementine",           NULL,             NULL,     1 << 6,       0,           -1       },
	{ "TelegramDesktop",      NULL,             NULL,     1 << 6,       0,           -1       },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                         KEY,      view,      {.ui = 1 << TAG} }, \
	{ ALTKEY|ShiftMask,               KEY, toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,               KEY,      tag,       {.ui = 1 << TAG} }, \
	{ ALTKEY|ControlMask|ShiftMask,   KEY, toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/bash", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };
static const char *guifmcmd[]  = { GUIFM, NULL };
static const char *calculatorcmd[]  = { CALCULATOR, NULL };

static const Key keys[] = {
  /* launchs */
	/* modifier                     key        function        argument */
  { MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
  { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
  { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = guifmcmd } },
  { MODKEY|ShiftMask,             XK_q,      spawn,          {.v = calculatorcmd } },
  { MODKEY,                       XK_t,      spawn,          SHCMD(SCRIPTSDIR "/calendar --popup &") },
  // FIXME
  { MODKEY|ShiftMask,             XK_v,      spawn,          SHCMD("pkexec env DISPLAY=$DISPLAY XAUTHORITY=$XAUTHORITY " VPN) },

  /* menus */
	/* modifier                     key        function        argument */
  { MODKEY,                       XK_w,      spawn,          SHCMD(SCRIPTSDIR "/wifi_menu") },
  { MODKEY,                       XK_b,      spawn,          SHCMD(SCRIPTSDIR "/bluetooth_menu") },
  { MODKEY,                       XK_x,      spawn,          SHCMD(SCRIPTSDIR "/powermenu") },
  
  /* functions */
	/* modifier                     key                        function        argument */
  { MODKEY,                       XK_c,                      killclient,     {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,                      quit,           {0} },
  { 0,                            XK_Print,                  spawn,          SHCMD(SCRIPTSDIR "/screenshot") },
  { ShiftMask,                    XK_Print,                  spawn,          SHCMD(SCRIPTSDIR "/screenshot -s") },
  { MODKEY|ControlMask,           XK_r,                      spawn,          SHCMD(SCRIPTSDIR "/toggle_redshift") },
  { MODKEY,                       XK_comma,                  spawn,          SHCMD(SCRIPTSDIR "/toggle_touchpad") },
  { MODKEY,                       XK_period,                 spawn,          SHCMD(SCRIPTSDIR "/toggle_touchscreen") },
  { MODKEY|ShiftMask,             XK_n,                      spawn,          SHCMD(SCRIPTSDIR "/dpms_on") },
  { MODKEY|ShiftMask,             XK_m,                      spawn,          SHCMD(SCRIPTSDIR "/dpms_off") },
  { 0,                            XK_F12,                    spawn,          SHCMD("clementine -f") },
  { 0,                            XK_F11,                    spawn,          SHCMD("clementine -t") },
  { 0,                            XK_F10,                    spawn,          SHCMD("clementine -r") },
  { 0,                            XF86XK_MonBrightnessUp,    spawn,          SHCMD("light -A 12 && light -O && brightness &") },
  { 0,                            XF86XK_MonBrightnessDown,  spawn,          SHCMD("light -U 12 && light -O && brightness &") },
  { 0,                            XF86XK_AudioMute,          spawn,          SHCMD(SCRIPTSDIR "/volume -m") },
  { 0,                            XF86XK_AudioRaiseVolume,   spawn,          SHCMD(SCRIPTSDIR "/volume -u") },
  { 0,                            XF86XK_AudioLowerVolume,   spawn,          SHCMD(SCRIPTSDIR "/volume -d") },
  { 0,                            XF86XK_AudioMicMute,       spawn,          SHCMD(SCRIPTSDIR "/microphone -m") },

  /* layout */
	/* modifier                     key        function        argument */
  { MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
  { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
  { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
  { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
  { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
  { MODKEY,                       XK_f,      zoom,           {0} },
  { MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
  { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ ALTKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ ALTKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },

  /* tags */
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_a,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_a,      tag,            {.ui = ~0 } },
	TAGKEYS(                        XK_grave,                  6)
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
