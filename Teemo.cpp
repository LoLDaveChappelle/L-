
#include "stdafx.h"
#include "PluginSDK.h"
#include "Teemo.h"

PluginSetup("Teemo");
/*
 * Skills
 */
IMenuOption* Blinding_Dart;
IMenuOption* Move_Quick;
IMenuOption* Toxic_Shot;
IMenuOption* Noxious_Trap;

/*
 * Drawing
 */
IMenuOption* DrawQ;
IMenuOption* DrawRange;

/*
 * Menu
 */
IMenu* Menu;
IMenu* SubMenu;
IMenu* Skins;
IMenu* Drawing;

/*
 * more spells
 */
ISpell2* Q;
ISpell2* W;
ISpell2* E;
ISpell2* R;

#pragma region Events
void MenuItem()
{
	/*
	 * Draw Main Menu
	 */
	Menu = GPluginSDK->AddMenu("Teemo");

	/*
	 * Draw category Spells
	 */
	SubMenu = Menu->AddMenu("Spells");


	/*
	* Draw category Draw
	*/
	Drawing = Menu->AddMenu("Draw");


	/*
	 * Draw category Skins
	 */
	Skins = Menu->AddMenu("Skins");


	/*
	 * KS MODE OPTION
	 */
	Menu->CheckBox("KS MODE", true);

	/*
	 * Skill category options
	 */
	Blinding_Dart = SubMenu->CheckBox("Use Q", true);
	Move_Quick = SubMenu->CheckBox("Use W", true);
	Toxic_Shot = SubMenu->CheckBox("Use E", true);
	Noxious_Trap = SubMenu->CheckBox("Use R", true);

	/*
	 * Draw category options
	 */
	DrawQ = Drawing->CheckBox("Draw Q", true);
	DrawRange = Drawing->AddInteger("Range:", 1, 255, 255);

	/*
	 * Skins category options
	 */
	Skins->CheckBox("Enabled", false);
	Skins->AddInteger("Skin", 1, 255, 255);

}

/*
 * Assigns Q W E R spells
 */
void LoadSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, true, false, kCollidesWithWalls);
	W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, kCollidesWithNothing);
	E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, true, false, kCollidesWithNothing);
	R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, false, kCollidesWithNothing);

	/*
	 * Gets the rane of the spell
	 * ---NEED TO FIND A BETTER WAY TO DO THIS!---
	 */
	Q->SetOverrideRange(600);

}

/*
 * Does Combo
 */
void Combo()
{
	if (Blinding_Dart->Enabled())
	{
		Q->CastOnTarget(GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range()));
	}
}


PLUGIN_EVENT(void) OnOrbwalkBeforeAttack(IUnit* Target)
{
}

PLUGIN_EVENT(void) OnOrbwalkAttack(IUnit* Source, IUnit* Target)
{

}



// Return an IUnit object here to force the orbwalker to select it for this tick
PLUGIN_EVENT(IUnit*) OnOrbwalkingFindTarget()
{
	return nullptr;
}

PLUGIN_EVENT(void) OnOrbwalkTargetChange(IUnit* OldTarget, IUnit* NewTarget)
{

}

PLUGIN_EVENT(void) OnOrbwalkNonKillableMinion(IUnit* NonKillableMinion)
{

}


/*
 * Finds "mode"
 */
PLUGIN_EVENT(void) OnGameUpdate()
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		Combo();
	}
}




PLUGIN_EVENT(void) OnOrbwalkAfterAttack(IUnit* Source, IUnit* Target)
{


}

/*
 * Draw
 */
PLUGIN_EVENT(void) OnRender()
{
	if (DrawQ->Enabled())
	{
		GPluginSDK->GetRenderer()->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range());
	}
}

PLUGIN_EVENT(void) OnSpellCast(CastedSpell const& Args)
{

}

PLUGIN_EVENT(void) OnUnitDeath(IUnit* Source)
{

}

PLUGIN_EVENT(void) OnCreateObject(IUnit* Source)
{

}

PLUGIN_EVENT(void) OnDestroyObject(IUnit* Source)
{

}

PLUGIN_EVENT(void) OnDoCast(CastedSpell const& Args)
{
}

PLUGIN_EVENT(void) OnInterruptible(InterruptibleSpell const& Args)
{

}

PLUGIN_EVENT(void) OnGapCloser(GapCloserSpell const& Args)
{

}

// Called when issuing an order (e.g move, attack, etc.)
// Return false to stop order from executing
PLUGIN_EVENT(bool) OnIssueOrder(IUnit* Source, DWORD OrderIdx, Vec3* Position, IUnit* Target)
{
	return true;
}

PLUGIN_EVENT(void) OnBuffAdd(IUnit* Source, void* BuffData)
{

}

PLUGIN_EVENT(void) OnBuffRemove(IUnit* Source, void* BuffData)
{

}

PLUGIN_EVENT(void) OnGameEnd()
{

}

PLUGIN_EVENT(void) OnLevelUp(IUnit* Source, int NewLevel)
{

}

// Only called for local player, before the spell packet is sent
PLUGIN_EVENT(void) OnPreCast(int Slot, IUnit* Target, Vec3* StartPosition, Vec3* EndPosition)
{
}

PLUGIN_EVENT(void) OnDash(UnitDash* Args)
{

}

PLUGIN_EVENT(void) OnD3DPresent(void* Direct3D9DevicePtr)
{

}

PLUGIN_EVENT(void) OnD3DPreReset(void* Direct3D9DevicePtr)
{

}

PLUGIN_EVENT(void) OnD3DPostReset(void* Direct3D9DevicePtr)
{

}

PLUGIN_EVENT(void) OnRenderBehindHUD()
{

}

// Return false to set this message as handled
PLUGIN_EVENT(bool) OnWndProc(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	return true;
}

PLUGIN_EVENT(void) OnEnterVisible(IUnit* Source)
{

}

PLUGIN_EVENT(void) OnExitVisible(IUnit* Source)
{

}
#pragma endregion

// Called when plugin is first loaded
PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	// Initializes global interfaces for core access
	PluginSDKSetup(PluginSDK);

	GEventManager->AddEventHandler(kEventOrbwalkBeforeAttack, OnOrbwalkBeforeAttack);
	GEventManager->AddEventHandler(kEventOrbwalkOnAttack, OnOrbwalkAttack);
	GEventManager->AddEventHandler(kEventOrbwalkAfterAttack, OnOrbwalkAfterAttack);
	GEventManager->AddEventHandler(kEventOrbwalkFindTarget, OnOrbwalkingFindTarget);
	GEventManager->AddEventHandler(kEventOrbwalkTargetChange, OnOrbwalkTargetChange);
	GEventManager->AddEventHandler(kEventOrbwalkNonKillableMinion, OnOrbwalkNonKillableMinion);
	GEventManager->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->AddEventHandler(kEventOnRender, OnRender);
	GEventManager->AddEventHandler(kEventOnSpellCast, OnSpellCast);
	GEventManager->AddEventHandler(kEventOnUnitDeath, OnUnitDeath);
	GEventManager->AddEventHandler(kEventOnCreateObject, OnCreateObject);
	GEventManager->AddEventHandler(kEventOnDestroyObject, OnDestroyObject);
	GEventManager->AddEventHandler(kEventOnDoCast, OnDoCast);
	GEventManager->AddEventHandler(kEventOnInterruptible, OnInterruptible);
	GEventManager->AddEventHandler(kEventOnGapCloser, OnGapCloser);
	GEventManager->AddEventHandler(kEventOnIssueOrder, OnIssueOrder);
	GEventManager->AddEventHandler(kEventOnBuffAdd, OnBuffAdd);
	GEventManager->AddEventHandler(kEventOnBuffRemove, OnBuffRemove);
	GEventManager->AddEventHandler(kEventOnGameEnd, OnGameEnd);
	GEventManager->AddEventHandler(kEventOnLevelUp, OnLevelUp);
	GEventManager->AddEventHandler(kEventOnPreCast, OnPreCast);
	GEventManager->AddEventHandler(kEventOnDash, OnDash);
	GEventManager->AddEventHandler(kEventOnD3DPresent, OnD3DPresent);
	GEventManager->AddEventHandler(kEventOnD3DPreReset, OnD3DPreReset);
	GEventManager->AddEventHandler(kEventOnD3DPostReset, OnD3DPostReset);
	GEventManager->AddEventHandler(kEventOnRenderBehindHud, OnRenderBehindHUD);
	GEventManager->AddEventHandler(kEventOnWndProc, OnWndProc);
	GEventManager->AddEventHandler(kEventOnEnterVisible, OnEnterVisible);
	GEventManager->AddEventHandler(kEventOnExitVisible, OnExitVisible);
	MenuItem();
	LoadSpells();
}

// Called when plugin is unloaded
PLUGIN_API void OnUnload()
{
	GEventManager->RemoveEventHandler(kEventOrbwalkBeforeAttack, OnOrbwalkBeforeAttack);
	GEventManager->RemoveEventHandler(kEventOrbwalkOnAttack, OnOrbwalkAttack);
	GEventManager->RemoveEventHandler(kEventOrbwalkAfterAttack, OnOrbwalkAfterAttack);
	GEventManager->RemoveEventHandler(kEventOrbwalkFindTarget, OnOrbwalkingFindTarget);
	GEventManager->RemoveEventHandler(kEventOrbwalkTargetChange, OnOrbwalkTargetChange);
	GEventManager->RemoveEventHandler(kEventOrbwalkNonKillableMinion, OnOrbwalkNonKillableMinion);
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
	GEventManager->RemoveEventHandler(kEventOnSpellCast, OnSpellCast);
	GEventManager->RemoveEventHandler(kEventOnUnitDeath, OnUnitDeath);
	GEventManager->RemoveEventHandler(kEventOnCreateObject, OnCreateObject);
	GEventManager->RemoveEventHandler(kEventOnDestroyObject, OnDestroyObject);
	GEventManager->RemoveEventHandler(kEventOnDoCast, OnDoCast);
	GEventManager->RemoveEventHandler(kEventOnInterruptible, OnInterruptible);
	GEventManager->RemoveEventHandler(kEventOnGapCloser, OnGapCloser);
	GEventManager->RemoveEventHandler(kEventOnIssueOrder, OnIssueOrder);
	GEventManager->RemoveEventHandler(kEventOnBuffAdd, OnBuffAdd);
	GEventManager->RemoveEventHandler(kEventOnBuffRemove, OnBuffRemove);
	GEventManager->RemoveEventHandler(kEventOnGameEnd, OnGameEnd);
	GEventManager->RemoveEventHandler(kEventOnLevelUp, OnLevelUp);
	GEventManager->RemoveEventHandler(kEventOnPreCast, OnPreCast);
	GEventManager->RemoveEventHandler(kEventOnDash, OnDash);
	GEventManager->RemoveEventHandler(kEventOnD3DPresent, OnD3DPresent);
	GEventManager->RemoveEventHandler(kEventOnD3DPreReset, OnD3DPreReset);
	GEventManager->RemoveEventHandler(kEventOnD3DPostReset, OnD3DPostReset);
	GEventManager->RemoveEventHandler(kEventOnRenderBehindHud, OnRenderBehindHUD);
	GEventManager->RemoveEventHandler(kEventOnWndProc, OnWndProc);
	GEventManager->RemoveEventHandler(kEventOnEnterVisible, OnEnterVisible);
	GEventManager->RemoveEventHandler(kEventOnExitVisible, OnExitVisible);
	Menu->Remove();
}

