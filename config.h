/* See LICENSE file for copyright and license details. */
#include "gaplessgrid.c"

/* appearance */
static const unsigned int gappx     = 6;        /* gap pixel between windows */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "SauceCodePro Nerd Font:size=11" };
static const char dmenufont[]       = "SauceCodePro Nerd Font:size=11";

// gruvbox
static const char col_gb_bg[]        = "#282828";
static const char col_gb_fg[]        = "#ebdbb2";

static const char col_gb_red1[]     = "#cc241d";
static const char col_gb_red2[]     = "#fb4934";

static const char col_gb_green1[]   = "#98971a";
static const char col_gb_green2[]   = "#b8bb26";

static const char col_gb_yellow1[]  = "#d79921";
static const char col_gb_yellow2[]  = "#fabd2f";

static const char col_gb_blue1[]    = "#458588";
static const char col_gb_blue2[]    = "#83a598";

static const char col_gb_purple1[]  = "#b16286";
static const char col_gb_purple2[]  = "#83869b";

static const char col_gb_aqua1[]    = "#689d6a";
static const char col_gb_aqua2[]    = "#8ec07c";

static const char col_gb_gray1[]    = "#a89984";
static const char col_gb_gray2[]    = "#928374";

static const char col_gb_orange1[]  = "#d65d0e";
static const char col_gb_orange2[]  = "#fe8019";
// gruvbox

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]     = { col_gb_gray2,   col_gb_bg,      col_gb_bg },
	[SchemeSel]      = { col_gb_orange2, col_gb_bg,      col_gb_orange2 },
	[SchemeSel2]     = { col_gb_fg,      col_gb_bg,      col_gb_bg },
	[SchemeUrgent]   = { col_gb_fg,      col_gb_bg,      col_gb_bg },
	[SchemeTitle]    = { col_gb_fg,      col_gb_bg,      col_gb_bg },
	[SchemeLt]       = { col_gb_orange2, col_gb_bg,      col_gb_bg },
	[SchemeNotify]   = { col_gb_red1,    col_gb_bg,      col_gb_bg },
	[SchemeStatus]   = { col_gb_aqua2,   col_gb_bg,      col_gb_bg },
	[SchemeIndOff]   = { col_gb_green2,  col_gb_bg,      col_gb_bg },
	[SchemeIndOn]    = { col_gb_blue2,   col_gb_bg,      col_gb_bg },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };
static const char *tagsalt[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           -1 },
	{ "firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Google-chrome",NULL,   NULL,       1 << 7,       0,           -1 },
	{ "Slack",    NULL,       NULL,       1 << 6,       0,           -1 },
	{ "Guake",    NULL,       NULL,       ~0,           1,           -1 },
	{ "copyq",    NULL,       NULL,       0,            1,           -1 },
	{ "Hexchat",  NULL,       NULL,       1 << 4,       0,           -1 },
	{ NULL,       NULL,       "Cmus",     1 << 5,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "響",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
	{ "ﱖ",      gaplessgrid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define SUPERMOD Mod4Mask|Mod1Mask
#define ALTMOD Mod1Mask

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* helper for launching gtk application */
#define GTKCMD(cmd) { .v = (const char*[]){ "/usr/bin/gtk-launch", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *termcmd[]  = { "gnome-terminal", NULL };

static const Arg tagexec[] = {
	{ .v = termcmd },
	GTKCMD("org.gnome.Nautilus.desktop"),
	GTKCMD("visual-studio-code.desktop"),
	SHCMD("lxterminal -t AlsaMixer -e /usr/bin/alsamixer"),
	GTKCMD("discord"),
	GTKCMD("cmus"),
	{ .v = termcmd },
	GTKCMD("personal-firefox"),
	GTKCMD("firefox")
};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          SHCMD("rofi -show run") },
	{ ALTMOD|ShiftMask,             XK_x,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_e,      spawn,          SHCMD("nautilus") },
	{ 0,			  XF86XK_AudioLowerVolume, spawn,          SHCMD("amixer set Master 5%-") },
	{ 0,			  XF86XK_AudioRaiseVolume, spawn,          SHCMD("amixer set Master 5%+") },
	{ 0,			  XF86XK_AudioMute,        spawn,          SHCMD("amixer set Master toggle") },
	{ MODKEY,                       XK_Menu,   spawn,          SHCMD("rofi -show combi") },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("rofi -show combi") },
	{ MODKEY|ControlMask,           XK_p,      spawn,          SHCMD("passmenu_rofi") },
	{ MODKEY|ControlMask,           XK_Menu,   spawn,          SHCMD("passmenu_rofi") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ ALTMOD,                       XK_Tab,    focusstack,     {.i = +1 } },
	{ ALTMOD|ShiftMask,             XK_Tab,    focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ ALTMOD,                       XK_grave,  view,           {0} },
	{ ALTMOD|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_Tab,    shiftview,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Tab,    shiftview,      {.i = -1 } },
	{ MODKEY,                       XK_j,      togglealttag,   {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button2,        spawntag,       {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

