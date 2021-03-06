/*
 * Copyright (C) 2013  BlizzLikeGroup
 * BlizzLikeCore integrates as part of this file: CREDITS.md and LICENSE.md
 */

/* ScriptData
Name: Boss_jandicebarov
Complete(%): 100
Comment:
Category: Scholomance
EndScriptData */

#include "ScriptPCH.h"

#define SPELL_CURSEOFBLOOD          24673
//#define SPELL_ILLUSION              17773

//Spells of Illusion of Jandice Barov
#define SPELL_CLEAVE                15584

struct boss_jandicebarovAI : public ScriptedAI
{
    boss_jandicebarovAI(Creature* c) : ScriptedAI(c) {}

    uint32 CurseOfBlood_Timer;
    uint32 Illusion_Timer;
    //uint32 Illusioncounter;
    uint32 Invisible_Timer;
    bool Invisible;

    void Reset()
    {
        CurseOfBlood_Timer = 15000;
        Illusion_Timer = 30000;
        Invisible_Timer = 3000;                             //Too much too low?
        Invisible = false;
    }

    void EnterCombat(Unit* /*who*/)
    {
    }

    void SummonIllusions(Unit* victim)
    {
        if (Creature* Illusion = DoSpawnCreature(11439, irand(-9,9), irand(-9,9), 0, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 60000))
            Illusion->AI()->AttackStart(victim);
    }

    void UpdateAI(const uint32 diff)
    {
        if (Invisible && Invisible_Timer <= diff)
        {
            //Become visible again
            me->setFaction(14);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetDisplayId(11073);     //Jandice Model
            Invisible = false;
        } else if (Invisible)
        {
            Invisible_Timer -= diff;
            //Do nothing while invisible
            return;
        }

        //Return since we have no target
        if (!UpdateVictim())
            return;

        //CurseOfBlood_Timer
        if (CurseOfBlood_Timer <= diff)
        {
            //Cast
            DoCast(me->getVictim(), SPELL_CURSEOFBLOOD);

            //45 seconds
            CurseOfBlood_Timer = 30000;
        } else CurseOfBlood_Timer -= diff;

        //Illusion_Timer
        if (!Invisible && Illusion_Timer <= diff)
        {

            //Inturrupt any spell casting
            me->InterruptNonMeleeSpells(false);
            me->setFaction(35);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetDisplayId(11686);  // Invisible Model
            DoModifyThreatPercent(me->getVictim(),-99);

            //Summon 10 Illusions attacking random gamers
            Unit* pTarget = NULL;
            for (uint8 i = 0; i < 10; ++i)
            {
                pTarget = SelectUnit(SELECT_TARGET_RANDOM,0);
                if (pTarget)
                    SummonIllusions(pTarget);
            }
            Invisible = true;
            Invisible_Timer = 3000;

            //25 seconds until we should cast this agian
            Illusion_Timer = 25000;
        } else Illusion_Timer -= diff;

        //            //Illusion_Timer
        //            if (Illusion_Timer <= diff)
        //            {
        //                  //Cast
        //                DoCast(me->getVictim(), SPELL_ILLUSION);
        //
        //                  //3 Illusion will be summoned
        //                  if (Illusioncounter < 3)
        //                  {
        //                    Illusion_Timer = 500;
        //                    ++Illusioncounter;
        //                  }
        //                  else {
        //                      //15 seconds until we should cast this again
        //                      Illusion_Timer = 15000;
        //                      Illusioncounter = 0;
        //                  }
        //
        //            } else Illusion_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

// Illusion of Jandice Barov Script

struct mob_illusionofjandicebarovAI : public ScriptedAI
{
    mob_illusionofjandicebarovAI(Creature* c) : ScriptedAI(c) {}

    uint32 Cleave_Timer;

    void Reset()
    {
        Cleave_Timer = 2000 + rand()%6000;
        me->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_MASK_MAGIC, true);
    }

    void EnterCombat(Unit* /*who*/)
    {
    }

    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!UpdateVictim())
            return;

        //Cleave_Timer
        if (Cleave_Timer <= diff)
        {
            //Cast
            DoCast(me->getVictim(), SPELL_CLEAVE);

            //5-8 seconds
            Cleave_Timer = 5000 + rand()%3000;
        } else Cleave_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_jandicebarov(Creature* pCreature)
{
    return new boss_jandicebarovAI (pCreature);
}

CreatureAI* GetAI_mob_illusionofjandicebarov(Creature* pCreature)
{
    return new mob_illusionofjandicebarovAI (pCreature);
}

void AddSC_boss_jandicebarov()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_jandice_barov";
    newscript->GetAI = &GetAI_boss_jandicebarov;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_illusionofjandicebarov";
    newscript->GetAI = &GetAI_mob_illusionofjandicebarov;
    newscript->RegisterSelf();
}

