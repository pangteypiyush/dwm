/* See LICENSE file for copyright and license details. */
#include "gaplessgrid.c"

/* appearance */
static const unsigned int gappx     = 6;        /* gap pixel between windows */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "SauceCodePro Nerd Font:size=11" };
static const char dmenufont[]       = "SauceCodePro Nerd Font:size=11";
static const char col_gray1[]       = "#262626";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#000000";
static const char col_cyan[]        = "#ffcc00";

static const char col_wall[]        = "#262626";
static const char col_blue[]        = "#2f9dfb";
static const char col_blue2[]       = "#005fff";
static const char col_yellow[]      = "#fcba04";
static const char col_yellow_wall[] = "#7e5f22";
static const char col_white[]       = "#f3f3f3";
static const char col_green[]       = "#5faf00";
static const char col_red1[]        = "#a50104";
static const char col_red2[]        = "#590004";
static const char col_red3[]        = "#250001";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]     = { col_gray3,   col_wall,    col_gray2 },
	[SchemeSel]      = { col_wall,    col_yellow,  col_yellow },
	[SchemeSel2]     = { col_gray3,   col_yellow_wall,col_gray2},
	[SchemeUrgent]   = { col_gray3,   col_wall,    col_gray2},
	[SchemeTitle]    = { col_gray3,   col_wall,    col_gray2 },
	[SchemeLt]       = { col_yellow,  col_wall,    col_gray2 },
	[SchemeNotify]   = { col_blue2,   col_wall,    col_gray2 },
	[SchemeStatus]   = { col_yellow,  col_wall,    col_gray2 },
	[SchemeIndOff]   = { col_green,   col_wall,    col_gray2 },
	[SchemeIndOn]    = { col_red1,    col_wall,    col_gray2 },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
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

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "gnome-terminal", NULL };

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
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

