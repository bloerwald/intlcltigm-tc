-- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Issue 3132: Horde Brewfest Vendors
-- add Ray'ma <Brew of the Month Club> (27489)
DELETE FROM `creature` WHERE `id`=27489;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES
(42662,27489,1,1,1,0,0,1472.608,-4209.172,43.26931,4.433136,600,0,0,7500,1,0,0,0,0);
-- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Issue 3563: Mistcaller Yngvar
-- Deletes incorrectly spawned Mistcaller Yngvar
DELETE FROM `creature` WHERE `id`=34965;
-- Spawns missing Spell Focus for Mistcaller's Cave
DELETE FROM `gameobject` WHERE `guid`=365;
INSERT INTO `gameobject` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES 
(365,300006,571,1,1,10184.8,1184.6,75.892,2.7989,0,0,0.985356,0.170509,300,0,1);
-- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Issue 3635: The Test of Skulls, Somnus
-- Spawn Somnus (12900) NPC needed for The Test of Skulls, Somnus (6583) quest fix by shlomi1515
SET @NPC  :=12900;
UPDATE `creature_template` SET AIName='SmartAI', Mechanic_Immune_Mask=2147483647 WHERE entry=@NPC;
DELETE FROM `creature` WHERE id=@NPC;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES
(42880,@NPC,0,1,1,0,0,-10444.5,-4096.17,28.9469,2.91185,300,0,0,38844,0,2,0,0,0);
DELETE FROM `smart_scripts` WHERE `entryorguid`=@NPC AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@NPC,0,0,0,13,0,100,0,75000,75000,75000,75000,11,20989,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Somnus - Target is Casting - Cast Sleep'),
(@NPC,0,1,0,13,0,100,0,85000,85000,85000,85000,11,12882,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Somnus - Target is Casting - Cast Wing Flap'),
(@NPC,0,2,0,0,0,100,0,0,5000,30000,30000,11,20667,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Somnus - IC - Cast Corrosive Acid Breath'),
(@NPC,0,3,0,0,0,100,0,7000,9000,14000,20000,11,18368,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Somnus - IC - Cast Strike');
-- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Issue 3678: Joys of Omosh
-- Orokk Omosh SAI
SET @ENTRY := 7790;
SET @QUEST := 2755;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
UPDATE `quest_template` SET `StartScript`=0,`CompleteScript`=0 WHERE `id`=@QUEST;
DELETE FROM `quest_start_scripts` WHERE `id`=@QUEST;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@ENTRY,@ENTRY*100);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,19,0,100,0,@QUEST,0,0,0,80,@ENTRY*100,0,2,0,0,0,1,0,0,0,0,0,0,0, 'Orokk Omosh - On Quest Accept - Run Script'),
(@ENTRY*100,9,0,0,0,0,100,0,0,0,0,0,5,10,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Orokk Omosh - On Script - Start Dancing'),
(@ENTRY*100,9,1,0,0,0,100,0,30000,30000,0,0,5,26,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Orokk Omosh - On Script - Stop Dancing'),
(@ENTRY*100,9,2,0,0,0,100,0,33000,33000,0,0,15,@QUEST,0,0,0,0,7,0,0,0,0,0,0,0,0, 'Orokk Omosh - On Script - Quest Credit');
-- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Issue 3679: Gnomer-gooooone!
-- Raschal the Courier SAI
SET @ENTRY := 7853;
SET @QUEST := 2843;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
UPDATE `quest_template` SET `StartScript`=0,`CompleteScript`=0 WHERE `id`=@QUEST;
DELETE FROM `quest_start_scripts` WHERE `id`=@QUEST;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@ENTRY,@ENTRY*100);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,19,0,100,0,@QUEST,0,0,0,80,@ENTRY*100,0,2,0,0,0,1,0,0,0,0,0,0,0, 'Scooty - On Quest Accept - Run Script'),
(@ENTRY*100,9,0,0,0,0,100,0,10000,10000,0,0,15,@QUEST,0,0,0,0,7,0,0,0,0,0,0,0,0, 'Scooty - On Script - Quest Credit');
-- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Issue 3680: Test of Faith
-- Dorn Plainstalker SAI
SET @ENTRY := 2986;
SET @QUEST := 1149;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
UPDATE `quest_template` SET `StartScript`=0,`CompleteScript`=0 WHERE `id`=@QUEST;
DELETE FROM `quest_start_scripts` WHERE `id`=@QUEST;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,19,0,100,0,@QUEST,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dorn Plainstalker - On Quest Accept - Say Line 0');
-- Text
DELETE FROM `db_script_string` WHERE `entry`=2000000042;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0, 'Until we meet again, brave one.',12,0,100,113,0,0, 'Dorn Plainstalker');
-- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Issue 3749: Frankly,It Makes No Sense
SET @Scorp := 21909; -- Arcano-Scorp
SET @CreditGuid := 84902; -- There is unused spawn of this
SET @Guid1 := 43463; -- TC team values should be set here -> add missing scorp spawn
SET @Guid2 := 43464; -- TC team values should be set here -> add missing scorp spawn
SET @Control1 := 37867; -- Trigger /connected with dismissing to make vehicle not attack master/
SET @Control1_1 := 37868; -- Control /apply control aura without target/
SET @Control2 := 37892; -- -//-
SET @Control2_2 := 37893; -- -//-
SET @Control3 := 37894; -- -//-
SET @Control3_3 := 37895; -- -//-
SET @Diametron := 21462; -- Greater Fellfire Diametron
-- Arcano-Scorp spells:
SET @Tag := 37851; -- Tag Greater Felfire Diemetradon
SET @Arcano_Cloak := 37917;
SET @Arcano_dismantle := 37919;
SET @Arcano_pince := 37918;
-- Add spawns for two missing Arcano-Scorps
UPDATE `creature_template` SET `AIName`='PetAI',`unit_flags`=512,`MovementType`=1,`spell4`=@Tag,`spell5`=@Arcano_Cloak,`spell6`=@Arcano_dismantle,`spell7`=@Arcano_pince WHERE `entry`=@Scorp;
UPDATE `creature` SET `MovementType`=1,`spawndist`=3,`position_x`=-3414.004,`position_y`=825.4113,`position_z`=-30.77301 WHERE `guid`=76655;
DELETE FROM `creature` WHERE `guid` IN (@Guid1,@Guid2,@CreditGuid);
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`MovementType`) VALUES
(@Guid1,@Scorp,530,1,1,-3414.294,813.9421,-31.12042,1.478481,30,3,0,1),
(@Guid2,@Scorp,530,1,1,-3408.508,795.8544,-31.42966,1.452154,30,3,0,1);
-- Spell script for trigger of control spell *will rewrite it once SAI spell script is released*
DELETE FROM `spell_scripts` WHERE `id` IN (@Control1,@Control2,@Control3);
INSERT INTO `spell_scripts` (`id`,`effindex`,`delay`,`command`,`datalong`,`datalong2`) VALUES
(@Control1,0,0,15,@Control1_1,2),
(@Control2,0,0,15,@Control2_2,2),
(@Control3,0,0,15,@Control3_3,2);
-- Limit @Tag only to Diametrons,also to ones not affected by it
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=17 AND `SourceEntry`=@Tag;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition` ,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(17,0,@Tag,0,0,31,1,3,@Diametron,0,0,0, '', 'Tag can only target Greater Felfire Diametrons'),
(17,0,@Tag,0,0,1,1,@Tag,0,0,1,0, '', 'Tag cannot be casted on tagged Diametrons');
-- Limit Arcano_Dismantle to not being able to hit self and cannot damage anything else beside Arcano-scorp
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=@Arcano_dismantle;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition` ,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(13,1,@Arcano_dismantle,0,0,33,1,0,1,0,1,0, '', 'Arcano-Dismantle effect 0 cannot hit self'),
(13,2,@Arcano_dismantle,0,0,33,1,0,1,0,1,0, '', 'Arcano-Dismantle effect 1 cannot hit self'),
(13,1,@Arcano_dismantle,0,0,31,0,3,@Scorp,0,0,0, '', 'Arcano-Dismantle effect 0 can hit only Arcano-Scorp'),
(13,2,@Arcano_dismantle,0,0,31,0,3,@Scorp,0,0,0, '', 'Arcano-Dismantle effect 1 can hit only Arcano-Scorp');
-- Limit @Arcano_pince to not being able to hit self and cannot damage anything else beside Arcano-scorp
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=@Arcano_pince;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition` ,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(13,1,@Arcano_pince,0,0,33,1,0,1,0,1,0, '', 'Arcano_pince effect 0 cannot hit self'),
(13,1,@Arcano_pince,0,0,31,0,3,@Scorp,0,0,0, '', 'Arcano_pince effect 0 can hit only Arcano-Scorp');
-- Add SAI for Greater Diametron to prevent some bugs
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@Diametron;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@Diametron;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@Diametron,0,0,0,0,0,100,0,4500,5000,5000,7000,11,37945,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Greater Fellfire Diametron - IC - Cast Fel Fireball'),
(@Diametron,0,1,0,0,0,100,0,1500,3000,15000,17000,11,37941,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Greater Fellfire Diametron - IC - Cast Flaming Wound'),
(@Diametron,0,2,3,8,0,100,0,@Tag,0,0,0,90,256,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Greater Fellfire Diametron - On hit by spell Tag - Set bytes to wipe aggro'),
(@Diametron,0,3,4,61,0,100,0,0,0,0,0,91,256,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Greater Fellfire Diametron - Linked with previous event - Remove bytes'),
(@Diametron,0,4,0,61,0,100,0,0,0,0,0,75,@Tag,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Greater Fellfire Diametron - Linked with previous event - Add Tag aura on self');
-- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Issue 3809: You Robot
DELETE FROM `creature_ai_scripts` WHERE creature_id=19851;
UPDATE `creature_template` SET AIName='SmartAI' WHERE `entry`=19851;
DELETE FROM `smart_scripts` WHERE entryorguid=19851;
INSERT INTO `smart_scripts` VALUES
(19851,0,0,0,9,0,100,0,8,25,15000,21000,11,35570,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Negatron - Cast Charge'),
(19851,0,1,0,9,0,100,0,0,5,15000,21000,11,34625,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Negatron - Cast Demolish'),
(19851,0,2,0,0,0,100,0,15000,19000,21000,25000,11,35565,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Negatron - Cast Earthquake'),
(19851,0,3,0,2,0,100,0,0,50,16000,22000,11,34624,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Negatron - Cast Frenzy at 50% HP'),
(19851,0,4,0,6,0,100,0,0,0,0,0,15,10248,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Negatron - Death - Quest Complete');
-- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Issue 3822: Deaths Door
-- Fix quest 10910 'Deaths Door'
-- Evergrove Druid SAI
SET @ENTRY := 22423;
UPDATE `creature_template` SET `inhabittype`=4,`AIName`= 'SmartAI' WHERE `entry`=@ENTRY;
UPDATE `creature_template_addon` SET `bytes1`=0,`bytes2`=1,`mount`=0,`emote`=0,`auras`=NULL WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,8,0,100,1,38782,0,0,0,11,38776,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Evergrove Druid - On hit by signal - transform to crow'),
(@ENTRY,0,1,2,61,0,100,0,0,0,0,0,19,33554432,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Evergrove Druid - On hit by signal - Remove field flag'),
(@ENTRY,0,2,3,61,0,100,0,0,0,0,0,69,0,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Evergrove Druid - On hit by signal - Follow player invoker'),
(@ENTRY,0,3,0,61,0,100,0,0,0,0,0,81,2,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Evergrove Druid - On hit by signal - Set npcflag = 2'),
(@ENTRY,0,4,5,64,0,100,1,0,0,0,0,11,39158,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Evergrove Druid - On gossip hello - transform to druid, since end point for follow can''t be player'),
(@ENTRY,0,5,0,61,0,100,0,0,0,0,0,41,60000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Evergrove Druid - After 60 sec - despawn'),
(@ENTRY,0,6,0,19,0,100,0,10904,0,0,0,41,10000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Evergrove Druid - On target accepted next quest - despawn'),
(@ENTRY,0,7,0,19,0,100,0,10911,0,0,0,41,10000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Evergrove Druid - On target accepted next quest - despawn'),
(@ENTRY,0,8,0,19,0,100,0,10912,0,0,0,41,10000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Evergrove Druid - On target accepted next quest - despawn'),
(@ENTRY,0,9,0,11,0,100,0,0,0,0,0,83,2,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Evergrove Druid - On Spawn - Remove quest flag');
-- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Issue 3930: Evil Draws Near
-- Teribus the Cursed is out of combat when is finally summoned by players
UPDATE `creature_template` SET `unit_flags`=`unit_flags`&~256 WHERE `entry`=22441; -- removing OOC
-- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DELETE FROM `creature` WHERE `guid`=42889;
INSERT INTO creature(`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`)
VALUES (42889,34675,0,1,1,0,0,-9133.91,355.333,92.3983,2.0151,300,0,0,1524,0,0,0,0,0);
-- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Issue 3761 Day of the Dead
-- Day of the Dead
SET @ENTRY := 34383; -- Catrina
DELETE FROM `creature_template_addon` WHERE `entry`=@ENTRY;
INSERT INTO `creature_template_addon` (`entry`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES
(@ENTRY,0,0,0,10,NULL);
UPDATE `quest_template` SET `RequiredRaces`=512 WHERE `Id`=14171;
UPDATE `quest_template` SET `RequiredRaces`=1024 WHERE `Id`=14169;
-- Invisibility aura for Cheerful Spirits
DELETE FROM `creature_template_addon` WHERE `entry` IN (35256,34435,34435,34478,34481,34484,34479,34483,34476,34477,34480,34482,35260,35261);
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES
(35256,0,0,0,0,0,30628), -- Cheerful Dalaran Spirit
(34435,0,0,0,0,0,30628), -- Cheerful Human Spirit
(34478,0,0,0,0,0,30628), -- Cheerful Dwarf Spirit
(34481,0,0,0,0,0,30628), -- Cheerful Gnome Spirit
(34484,0,0,0,0,0,30628), -- Cheerful Draenei Spirit
(34479,0,0,0,0,0,30628), -- Cheerful Night Elf Spirit
(34483,0,0,0,0,0,30628), -- Cheerful Blood Elf Spirit
(34476,0,0,0,0,0,30628), -- Cheerful Forsaken Spirit
(34477,0,0,0,0,0,30628), -- Cheerful Orc Spirit
(34480,0,0,0,0,0,30628), -- Cheerful Tauren Spirit
(34482,0,0,0,0,0,30628), -- Cheerful Troll Spirit
(35260,0,0,0,0,0,30628), -- Cheerful Aldor Spirit
(35261,0,0,0,0,0,30628); -- Cheerful Scryer Spirit
-- Quest relations
DELETE FROM `creature_questrelation` WHERE `id` IN (35256,34435,34435,34478,34481,34484,34479,34483,34476,34477,34480,34482,35260,35261);
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
(34435,13952),
(34476,14174),
(34477,14175),
(34478,14167),
(34479,14170),
(34480,14176),
(34481,14168),
(34482,14177),
(34483,14171),
(34484,14169),
(35256,14166),
(35260,14172),
(35261,14173);
DELETE FROM `creature_involvedrelation` WHERE `id` IN (35256,34435,34435,34478,34481,34484,34479,34483,34476,34477,34480,34482,35260,35261);
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(34435,13952),
(34476,14174),
(34477,14175),
(34478,14167),
(34479,14170),
(34480,14176),
(34481,14168),
(34482,14177),
(34483,14171),
(34484,14169),
(35256,14166),
(35260,14172),
(35261,14173);
-- Creature spawns for Day of the Dead Event
SET @GUID := 134848;
DELETE FROM `creature` WHERE `guid` BETWEEN @GUID AND @GUID+146;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@GUID,20102,530,1,1,0,0,3038.56,3635.53,144.012,3.32713,300,0,0,42,0,0,0,0,0),
(@GUID+1,35250,1,1,1,0,0,10066,2125.69,1329.66,1.12742,300,0,0,42,0,0,0,0,0),
(@GUID+2,35250,1,1,1,0,0,10058.4,2135.92,1330.81,4.55176,300,0,0,42,0,0,0,0,0),
(@GUID+3,35250,1,1,1,0,0,10045,2109.59,1330.2,0.224221,300,0,0,42,0,0,0,0,0),
(@GUID+4,35250,1,1,1,0,0,10053.8,2104.68,1330.93,1.5594,300,0,0,42,0,0,0,0,0),
(@GUID+5,35250,1,1,1,0,0,10052.9,2111.1,1330.06,1.93246,300,0,0,42,0,0,0,0,0),
(@GUID+6,35250,1,1,1,0,0,10062.2,2109.76,1330.92,2.08954,300,0,0,42,0,0,0,0,0),
(@GUID+7,35250,1,1,1,0,0,10063.5,2117.74,1330.03,3.55824,300,0,0,42,0,0,0,0,0),
(@GUID+8,35250,1,1,1,0,0,10059.1,2123.97,1330.28,5.04264,300,0,0,42,0,0,0,0,0),
(@GUID+9,35250,1,1,1,0,0,10052.9,2127.26,1330.13,3.93523,300,0,0,42,0,0,0,0,0),
(@GUID+10,34479,1,1,1,0,0,10061.5,2128.42,1330.17,2.73357,300,0,0,2442,2434,0,0,0,0),
(@GUID+11,35243,530,1,1,0,0,9404.91,-6859.42,15.101,4.17483,300,0,0,40,120,0,0,0,0),
(@GUID+12,35243,530,1,1,0,0,9411.01,-6855.19,14.9017,1.27278,300,0,0,40,120,0,0,0,0),
(@GUID+13,35243,530,1,1,0,0,9414.6,-6853.32,14.9361,2.67472,300,0,0,40,120,0,0,0,0),
(@GUID+14,35243,530,1,1,0,0,9415.1,-6848.51,15.1693,3.83318,300,0,0,40,120,0,0,0,0),
(@GUID+15,35249,0,1,1,0,0,-9350.81,171.018,61.7532,1.0198,300,0,0,42,0,0,0,0,0),
(@GUID+16,35253,1,1,1,0,0,1174.68,-4467.53,21.2746,0.833251,300,0,0,42,0,0,0,0,0),
(@GUID+17,35253,1,1,1,0,0,1182,-4463.02,21.2426,2.68915,300,0,0,42,0,0,0,0,0),
(@GUID+18,35253,1,1,1,0,0,1186.12,-4465.53,21.2886,1.73018,300,0,0,42,0,0,0,0,0),
(@GUID+19,35253,1,1,1,0,0,1176.79,-4460.38,21.4269,5.82603,300,0,0,42,0,0,0,0,0),
(@GUID+20,35251,1,1,1,0,0,1172.3,-4460.54,21.4697,6.19124,300,0,0,42,0,0,0,0,0),
(@GUID+21,35251,1,1,1,0,0,1180.91,-4471.22,21.1603,1.71055,300,0,0,42,0,0,0,0,0),
(@GUID+22,34483,530,1,1,0,0,9407.42,-6859.87,14.8699,3.93528,300,0,0,4890,7196,0,0,0,0),
(@GUID+23,35243,530,1,1,0,0,9409.6,-6847.61,15.5215,4.92881,300,0,0,40,120,0,0,0,0),
(@GUID+24,35243,530,1,1,0,0,9407.46,-6852.95,15.239,0.00436234,300,0,0,40,120,0,0,0,0),
(@GUID+25,35249,0,1,1,0,0,-9337.56,188.283,61.5117,3.72314,300,0,0,42,0,0,0,0,0),
(@GUID+26,35249,0,1,1,0,0,-9340.16,183.339,61.5512,0.349854,300,0,0,42,0,0,0,0,0),
(@GUID+27,35249,0,1,1,0,0,-9342.2,187.984,61.5586,5.25467,300,0,0,42,0,0,0,0,0),
(@GUID+28,35249,0,1,1,0,0,-9329.31,166.352,61.5815,1.76357,300,0,0,42,0,0,0,0,0),
(@GUID+29,35249,0,1,1,0,0,-9322.06,168.47,61.6066,2.40367,300,0,0,42,0,0,0,0,0),
(@GUID+30,35249,0,1,1,0,0,-9318.67,173.348,61.613,2.83957,300,0,0,42,0,0,0,0,0),
(@GUID+31,35249,0,1,1,0,0,-9346.44,171.041,61.5582,2.74061,300,0,0,42,0,0,0,0,0),
(@GUID+32,35249,0,1,1,0,0,-9344.05,175.877,61.5584,3.59669,300,0,0,42,0,0,0,0,0),
(@GUID+33,35249,0,1,1,0,0,-9349.19,176.153,61.726,5.18634,300,0,0,42,0,0,0,0,0),
(@GUID+34,35249,0,1,1,0,0,-9327.92,185.507,62.7096,4.07265,300,0,0,42,0,0,0,0,0),
(@GUID+35,34383,1,1,1,0,0,1184.43,-4467.28,21.3388,1.2079,300,0,0,12600,0,0,0,0,0),
(@GUID+36,34383,0,1,1,0,0,-9330.46,180.936,61.6792,4.1716,300,0,0,12600,0,0,0,0,0),
(@GUID+37,34382,1,1,1,0,0,1180.53,-4465.53,21.3293,0.944794,600,0,0,12600,0,0,0,0,0),
(@GUID+38,34382,0,1,1,0,0,-9327.6,178.975,61.6973,4.10484,600,0,0,12600,0,0,0,0,0),
(@GUID+39,34482,1,1,1,0,0,1181.51,-4469.65,21.2349,1.4121,300,0,0,2136,5751,0,0,0,0),
(@GUID+40,34435,0,1,1,0,0,-9354.72,167.942,61.665,0.27367,300,0,0,3052,0,0,0,0,0),
(@GUID+41,34477,1,1,1,0,0,1173.47,-4462.54,21.3309,0.60707,300,0,0,3052,0,0,0,0,0),
(@GUID+42,35256,571,1,65535,0,0,5831.01,751.564,641.134,3.40199,300,0,0,12600,0,0,0,0,0),
(@GUID+43,35254,571,1,65535,0,0,5829.42,754.776,640.729,5.14164,300,0,0,8508,7981,0,0,0,0),
(@GUID+44,35254,571,1,65535,0,0,5827.15,751.291,640.952,0.150437,300,0,0,8508,7981,0,0,0,0),
(@GUID+45,35254,571,1,65535,0,0,5830.31,746.699,641.251,1.36388,300,0,0,8508,7981,0,0,0,0),
(@GUID+46,35254,571,1,65535,0,0,5835.25,748.654,641.162,2.59303,300,0,0,8508,7981,0,0,0,0),
(@GUID+47,35254,571,1,65535,0,0,5835.24,754.043,641.008,3.64153,300,0,0,8508,7981,0,0,0,0),
(@GUID+48,35254,571,1,65535,0,0,5828.15,741.877,642.46,1.24607,300,0,0,8508,7981,0,0,0,0),
(@GUID+49,35254,571,1,65535,0,0,5846.77,755.676,640.68,0.837661,300,0,0,8508,7981,0,0,0,0),
(@GUID+50,35254,571,1,65535,0,0,5850.95,756.541,640.434,2.81294,300,0,0,8508,7981,0,0,0,0),
(@GUID+51,35254,571,1,65535,0,0,5848.22,760.619,641.147,4.64684,300,0,0,8508,7981,0,0,0,0),
(@GUID+52,35254,571,1,65535,0,0,5841.11,762.141,640.661,0.480303,300,0,0,8508,7981,0,0,0,0),
(@GUID+53,35244,0,1,1,0,0,1833.58,225.962,60.4294,4.33165,300,0,0,42,0,0,0,0,0),
(@GUID+54,35244,0,1,1,0,0,1828.46,224.586,60.4551,5.29769,300,0,0,42,0,0,0,0,0),
(@GUID+55,35244,0,1,1,0,0,1824.9,218.875,60.4469,0.0315971,300,0,0,42,0,0,0,0,0),
(@GUID+56,35244,0,1,1,0,0,1836.95,222.233,60.2385,3.22031,300,0,0,42,0,0,0,0,0),
(@GUID+57,35244,0,1,1,0,0,1834.67,215.873,60.1774,2.55665,300,0,0,42,0,0,0,0,0),
(@GUID+58,35244,0,1,1,0,0,1821.83,225.812,60.919,5.50582,300,0,0,42,0,0,0,0,0),
(@GUID+59,34476,0,1,1,0,0,1830.34,219.535,60.6017,4.58298,300,0,0,3052,0,0,0,0,0),
(@GUID+60,34382,571,1,65535,0,0,5844.1,764.778,640.546,4.20309,600,0,0,12600,0,0,0,0,0),
(@GUID+61,34382,0,1,1,0,0,1832.47,210.797,60.312,2.04222,600,0,0,12600,0,0,0,0,0),
(@GUID+62,34382,530,1,1,0,0,9406.42,-6864.02,14.8942,1.19424,600,0,0,12600,0,0,0,0,0),
(@GUID+63,34382,1,1,1,0,0,10058.2,2133,1329.66,4.43788,600,0,0,12600,0,0,0,0,0),
(@GUID+64,34382,1,1,1,0,0,-989.195,-59.6891,27.4632,5.21191,600,0,0,12600,0,0,0,0,0),
(@GUID+65,34382,530,1,1,0,0,-4320.01,-12433.4,17.9088,5.1906,600,0,0,12600,0,0,0,0,0),
(@GUID+66,34382,530,1,1,0,0,-1805.58,4911.74,-21.8346,1.35833,600,0,0,12600,0,0,0,0,0),
(@GUID+67,34382,0,1,1,0,0,-5151.65,-852.495,508.667,4.58185,600,0,0,12600,0,0,0,0,0),
(@GUID+68,34383,571,1,65535,0,0,5844.93,762.949,640.713,2.86791,300,0,0,12600,0,0,0,0,0),
(@GUID+69,34383,0,1,1,0,0,1828.96,210.695,60.2619,1.24504,300,0,0,12600,0,0,0,0,0),
(@GUID+70,34383,530,1,1,0,0,9403.71,-6861.68,15.0351,0.609119,300,0,0,12600,0,0,0,0,0),
(@GUID+71,34383,1,1,1,0,0,10067,2128.44,1329.66,3.57394,300,0,0,12600,0,0,0,0,0),
(@GUID+72,34383,1,1,1,0,0,-987.397,-58.6047,27.5876,4.96843,300,0,0,12600,0,0,0,0,0),
(@GUID+73,34383,530,1,1,0,0,-4317.46,-12431.3,17.755,5.11599,300,0,0,12600,0,0,0,0,0),
(@GUID+74,34383,530,1,1,0,0,-1809.42,4913.42,-21.8336,0.867451,300,0,0,12600,0,0,0,0,0),
(@GUID+75,34383,0,1,1,0,0,-5155.07,-854.489,508.115,5.0845,300,0,0,12600,0,0,0,0,0),
(@GUID+76,34480,1,1,1,0,0,-979.399,-75.0704,19.5113,0.118608,300,0,0,3052,0,0,0,0,0),
(@GUID+77,35252,1,1,1,0,0,-979.099,-78.4939,19.6825,0.8451,300,0,0,42,0,0,0,0,0),
(@GUID+78,35252,1,1,1,0,0,-979.773,-70.3366,19.8615,5.07447,300,0,0,42,0,0,0,0,0),
(@GUID+79,35252,1,1,1,0,0,-975.337,-71.6525,18.3695,3.78799,300,0,0,42,0,0,0,0,0),
(@GUID+80,35252,1,1,1,0,0,-975.356,-76.2146,18.7461,2.57848,300,0,0,42,0,0,0,0,0),
(@GUID+81,35252,1,1,1,0,0,-979.443,-57.4083,26.7673,4.68334,300,0,0,42,0,0,0,0,0),
(@GUID+82,34484,530,1,1,0,0,-4329.44,-12443.6,17.6841,5.62257,300,0,0,5589,3155,0,0,0,0),
(@GUID+83,35246,530,1,1,0,0,-4326.98,-12448.5,16.9294,5.47334,300,0,0,41,60,0,0,0,0),
(@GUID+84,35246,530,1,1,0,0,-4326.59,-12453.9,16.7549,0.721683,300,0,0,41,60,0,0,0,0),
(@GUID+85,35246,530,1,1,0,0,-4319.13,-12455.1,17.4243,2.4417,300,0,0,41,60,0,0,0,0),
(@GUID+86,35246,530,1,1,0,0,-4320.45,-12448.9,17.0584,3.68656,300,0,0,41,60,0,0,0,0),
(@GUID+87,35246,530,1,1,0,0,-4309.37,-12444,17.5071,3.15249,300,0,0,41,60,0,0,0,0),
(@GUID+88,35246,530,1,1,0,0,-4312.76,-12446.2,17.3102,1.3932,300,0,0,41,60,0,0,0,0),
(@GUID+89,35246,530,1,1,0,0,-4313.48,-12441,17.2002,5.26914,300,0,0,41,60,0,0,0,0),
(@GUID+90,35246,530,1,1,0,0,-4315.9,-12433.6,17.5953,2.19823,300,0,0,41,60,0,0,0,0),
(@GUID+91,35260,530,1,1,0,0,-1810.34,4923.26,-21.8439,5.41099,300,0,0,5589,3155,0,0,0,0),
(@GUID+92,35261,530,1,1,0,0,-1796.9,4928.76,-22.2745,3.23936,300,0,0,4890,7196,0,0,0,0),
(@GUID+93,35258,530,1,1,0,0,-1806.01,4925.33,-21.878,3.62813,300,0,0,4140,6443,0,0,0,0),
(@GUID+94,35258,530,1,1,0,0,-1812.25,4929.11,-21.6268,4.96723,300,0,0,4140,6443,0,0,0,0),
(@GUID+95,35258,530,1,1,0,0,-1814.69,4922.25,-22.0148,0.254842,300,0,0,4140,6443,0,0,0,0),
(@GUID+96,35258,530,1,1,0,0,-1809.16,4918.68,-21.982,1.82171,300,0,0,4140,6443,0,0,0,0),
(@GUID+97,35259,530,1,1,0,0,-1801.26,4929.1,-22.3108,6.17282,300,0,0,4140,6443,0,0,0,0),
(@GUID+98,35259,530,1,1,0,0,-1792.87,4928.28,-22.1848,2.99981,300,0,0,4140,6443,0,0,0,0),
(@GUID+99,35259,530,1,1,0,0,-1797.58,4924.28,-21.9414,1.31905,300,0,0,4140,6443,0,0,0,0),
(@GUID+100,35259,530,1,1,0,0,-1796.3,4933.33,-22.3432,4.54704,300,0,0,4140,6443,0,0,0,0),
(@GUID+101,34481,0,1,1,0,0,-5167.84,-870.949,506.706,1.024,300,0,0,2136,5751,0,0,0,0),
(@GUID+102,34478,0,1,1,0,0,-5165.9,-866.76,506.808,4.28811,300,0,0,3052,0,0,0,0,0),
(@GUID+103,35247,0,1,1,0,0,-5162.65,-873.025,507.206,1.00122,300,0,0,42,0,0,0,0,0),
(@GUID+104,35247,0,1,1,0,0,-5158.7,-872.414,507.406,2.72124,300,0,0,42,0,0,0,0,0),
(@GUID+105,35247,0,1,1,0,0,-5160.49,-869.137,507.265,4.21349,300,0,0,42,0,0,0,0,0),
(@GUID+106,35247,0,1,1,0,0,-5164.33,-869.728,507.01,5.69397,300,0,0,42,0,0,0,0,0),
(@GUID+107,35248,0,1,1,0,0,-5155,-856.249,508.059,1.51565,300,0,0,42,0,0,0,0,0),
(@GUID+108,35248,0,1,1,0,0,-5159.06,-867.484,507.333,0.859842,300,0,0,42,0,0,0,0,0),
(@GUID+109,35248,0,1,1,0,0,-5154.91,-867.566,507.758,2.45027,300,0,0,42,0,0,0,0,0),
(@GUID+110,35248,0,1,1,0,0,-5155.64,-863.343,507.652,4.05641,300,0,0,42,0,0,0,0,0),
(@GUID+111,35248,0,1,1,0,0,-5159.96,-863.16,507.247,5.49762,300,0,0,42,0,0,0,0,0),
(@GUID+112,18927,0,1,1,0,0,-8855.97,652.546,96.2675,5.07716,300,0,0,42,0,0,0,0,0),
(@GUID+113,18927,571,1,1,0,0,5678.09,658.93,647.134,0.088838,300,0,0,42,0,0,0,0,0),
(@GUID+114,18927,0,1,1,0,0,-8854.78,649.83,96.7417,1.43117,300,0,0,42,0,0,0,0,0),
(@GUID+115,18927,571,1,1,0,0,5719.3,687.257,645.752,5.72721,300,0,0,42,0,0,0,0,0),
(@GUID+116,19169,530,1,1,0,0,9659.86,-7115.63,14.3239,5.88552,300,0,0,42,0,0,0,0,0),
(@GUID+117,19169,571,1,1,0,0,5889.57,550.355,639.637,1.57167,300,0,0,42,0,0,0,0,0),
(@GUID+118,19169,571,1,1,0,0,5928.98,639.593,645.557,3.01052,300,0,0,42,0,0,0,0,0),
(@GUID+119,19169,530,1,1,0,0,9664.38,-7117.91,14.324,2.63397,300,0,0,42,0,0,0,0,0),
(@GUID+120,19148,0,1,1,0,0,-4914.82,-951.191,501.498,4.5773,300,0,0,42,0,0,0,0,0),
(@GUID+121,19148,0,1,1,0,0,-4915.33,-953.892,501.498,2.25016,300,0,0,42,0,0,0,0,0),
(@GUID+122,19171,530,1,1,0,0,-3910.91,-11612.4,-138.243,4.99941,300,0,0,42,0,0,0,0,0),
(@GUID+123,19171,530,1,1,0,0,-3909.22,-11614.8,-138.101,3.1765,300,0,0,42,0,0,0,0,0),
(@GUID+124,19172,0,1,1,0,0,-4826.78,-1175.89,502.193,2.45358,300,0,0,42,0,0,0,0,0),
(@GUID+125,19172,0,1,1,0,0,-4829.02,-1174.75,502.193,0.724139,300,0,0,42,0,0,0,0,0),
(@GUID+126,19173,1,1,1,0,0,9923.44,2496.95,1317.49,2.28359,300,0,0,42,0,0,0,0,0),
(@GUID+127,19173,1,1,1,0,0,9921.56,2499.58,1317.77,5.61996,300,0,0,42,0,0,0,0,0),
(@GUID+128,19178,0,1,1,0,0,1626.7,222.7,-43.1027,1.01229,300,0,0,42,0,0,0,0,0),
(@GUID+129,19178,0,1,1,0,0,1629.95,219.238,-43.1027,1.91079,300,0,0,42,0,0,0,0,0),
(@GUID+130,19177,1,1,1,0,0,1688.01,-4350.19,61.2691,2.56413,300,0,0,42,0,0,0,0,0),
(@GUID+131,19177,1,1,1,0,0,1685.07,-4352.88,61.7253,1.79601,300,0,0,42,0,0,0,0,0),
(@GUID+132,19176,1,1,1,0,0,-1241.98,81.7344,129.422,5.4992,300,0,0,42,0,0,0,0,0),
(@GUID+133,19176,1,1,1,0,0,-1242.68,76.7127,128.935,1.27376,300,0,0,42,0,0,0,0,0),
(@GUID+134,19175,1,1,1,0,0,1607.39,-4402.93,10.1664,3.11715,300,0,0,42,0,0,0,0,0),
(@GUID+135,19175,1,1,1,0,0,1603.36,-4404.49,9.30901,0.627438,300,0,0,42,0,0,0,0,0),
(@GUID+136,20102,1,1,1,0,0,6747.03,-4664.43,724.551,3.61009,300,0,0,42,0,0,0,0,0),
(@GUID+137,20102,1,1,1,0,0,-938.792,-3735.2,8.57162,3.66385,300,0,0,42,0,0,0,0,0),
(@GUID+138,20102,1,1,1,0,0,-7177.24,-3810.02,8.3753,0.711558,300,0,0,42,0,0,0,0,0),
(@GUID+139,20102,0,1,1,0,0,-14464.9,470.287,15.0369,5.96098,300,0,0,42,0,0,0,0,0),
(@GUID+140,20102,530,1,1,0,0,-1888.02,5400.44,-12.4278,5.97919,300,0,0,42,0,0,0,0,0),
(@GUID+141,20102,530,1,1,0,0,3035.51,3635.08,144.47,0.901821,300,0,0,42,0,0,0,0,0),
(@GUID+142,20102,1,1,1,0,0,6745.48,-4667.44,723.103,1.03712,300,0,0,42,0,0,0,0,0),
(@GUID+143,20102,1,1,1,0,0,-936.306,-3738.3,8.96324,3.35283,300,0,0,42,0,0,0,0,0),
(@GUID+144,20102,1,1,1,0,0,-7173.14,-3808.58,8.37043,3.3285,300,0,0,42,0,0,0,0,0),
(@GUID+145,20102,0,1,1,0,0,-14461.4,468.507,15.1232,2.66545,300,0,0,42,0,0,0,0,0),
(@GUID+146,20102,530,1,1,0,0,-1884.63,5397.52,-12.4278,2.51637,300,0,0,42,0,0,0,0,0);
-- Assignment of creatures to game event.
DELETE FROM `game_event_creature` WHERE `eventEntry`=51 AND `guid` BETWEEN @GUID AND @GUID+146;
INSERT INTO `game_event_creature` (`eventEntry`, `guid`) VALUES
(51,@GUID),(51,@GUID+1),(51,@GUID+2),(51,@GUID+3),(51,@GUID+4),(51,@GUID+5),
(51,@GUID+6),(51,@GUID+7),(51,@GUID+8),(51,@GUID+9),(51,@GUID+10),
(51,@GUID+11),(51,@GUID+12),(51,@GUID+13),(51,@GUID+14),(51,@GUID+15),
(51,@GUID+16),(51,@GUID+17),(51,@GUID+18),(51,@GUID+19),(51,@GUID+20),
(51,@GUID+21),(51,@GUID+22),(51,@GUID+23),(51,@GUID+24),(51,@GUID+25),
(51,@GUID+26),(51,@GUID+27),(51,@GUID+28),(51,@GUID+29),(51,@GUID+30),
(51,@GUID+31),(51,@GUID+32),(51,@GUID+33),(51,@GUID+34),(51,@GUID+35),
(51,@GUID+36),(51,@GUID+37),(51,@GUID+38),(51,@GUID+39),(51,@GUID+40),
(51,@GUID+41),(51,@GUID+42),(51,@GUID+43),(51,@GUID+44),(51,@GUID+45),
(51,@GUID+46),(51,@GUID+47),(51,@GUID+48),(51,@GUID+49),(51,@GUID+50),
(51,@GUID+51),(51,@GUID+52),(51,@GUID+53),(51,@GUID+54),(51,@GUID+55),
(51,@GUID+56),(51,@GUID+57),(51,@GUID+58),(51,@GUID+59),(51,@GUID+60),
(51,@GUID+61),(51,@GUID+62),(51,@GUID+63),(51,@GUID+64),(51,@GUID+65),
(51,@GUID+66),(51,@GUID+67),(51,@GUID+68),(51,@GUID+69),(51,@GUID+70),
(51,@GUID+71),(51,@GUID+72),(51,@GUID+73),(51,@GUID+74),(51,@GUID+75),
(51,@GUID+76),(51,@GUID+77),(51,@GUID+78),(51,@GUID+79),(51,@GUID+80),
(51,@GUID+81),(51,@GUID+82),(51,@GUID+83),(51,@GUID+84),(51,@GUID+85),
(51,@GUID+86),(51,@GUID+87),(51,@GUID+88),(51,@GUID+89),(51,@GUID+90),
(51,@GUID+91),(51,@GUID+92),(51,@GUID+93),(51,@GUID+94),(51,@GUID+95),
(51,@GUID+96),(51,@GUID+97),(51,@GUID+98),(51,@GUID+99),(51,@GUID+100),
(51,@GUID+101),(51,@GUID+102),(51,@GUID+103),(51,@GUID+104),(51,@GUID+105),
(51,@GUID+106),(51,@GUID+107),(51,@GUID+108),(51,@GUID+109),(51,@GUID+110),
(51,@GUID+111),(51,@GUID+112),(51,@GUID+113),(51,@GUID+114),(51,@GUID+115),
(51,@GUID+116),(51,@GUID+117),(51,@GUID+118),(51,@GUID+119),(51,@GUID+120),
(51,@GUID+121),(51,@GUID+122),(51,@GUID+123),(51,@GUID+124),(51,@GUID+125),
(51,@GUID+126),(51,@GUID+127),(51,@GUID+128),(51,@GUID+129),(51,@GUID+130),
(51,@GUID+131),(51,@GUID+132),(51,@GUID+133),(51,@GUID+134),(51,@GUID+135),
(51,@GUID+136),(51,@GUID+137),(51,@GUID+138),(51,@GUID+139),(51,@GUID+140),
(51,@GUID+141),(51,@GUID+142),(51,@GUID+143),(51,@GUID+144),(51,@GUID+145),
(51,@GUID+146);
-- Gameobject spawns
SET @GUID := 76237;
DELETE FROM `gameobject` WHERE `guid` BETWEEN @GUID AND @GUID+313;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@GUID,195066,1,1,1,-984.309,-72.3299,20.9918,0,0,0,0,1,180,100,1),
(@GUID+1,195069,0,1,1,-9330.98,181.918,62.7222,2.54818,0,0,0,1,180,100,1),
(@GUID+2,182807,530,1,1,9672.12,-7346.44,11.9311,-0.244346,0,0,0.121869,-0.992546,180,100,1),
(@GUID+3,195307,0,1,1,1780.5,269.08,59.8237,3.00195,0,0,0,1,180,100,1),
(@GUID+4,195090,0,1,1,-5155.34,-862.141,507.655,4.22449,0,0,0.856962,-0.515379,300,0,1),
(@GUID+5,195307,1,1,1,10054.2,2129.03,1329.66,-2.30383,0,0,0,1,180,100,1),
(@GUID+6,195307,0,1,1,1792.51,241.774,60.5867,-2.30383,0,0,0,1,180,100,1),
(@GUID+7,195307,1,1,1,10053.8,2127.78,1329.67,-2.30383,0,0,0,1,180,100,1),
(@GUID+8,195307,1,1,1,10049.7,2113.11,1329.68,-2.79252,0,0,0,1,180,100,1),
(@GUID+9,195087,0,1,1,-9333.99,181.712,61.5651,4.14018,0,0,0.87792,-0.478807,300,0,1),
(@GUID+10,195087,1,1,1,1177.92,-4467.1,21.3191,1.02726,0,0,0.49134,0.870968,300,0,1),
(@GUID+11,195067,1,1,1,1179.08,-4469.52,21.5266,1.0194,0,0,0.487916,0.87289,300,0,1),
(@GUID+12,195067,1,1,1,1174.65,-4455.39,21.539,1.12543,0,0,0.533485,0.845809,300,0,1),
(@GUID+13,195067,1,1,1,1186.5,-4461.7,21.136,1.23932,0,0,0.580757,0.814077,300,0,1),
(@GUID+14,195087,571,1,65535,5851.71,759.739,640.824,0.177921,0,0,0.088843,0.996046,300,0,1),
(@GUID+15,195087,0,1,1,1831.24,213.873,60.339,4.59476,0,0,0.747449,-0.66432,300,0,1),
(@GUID+16,195087,530,1,1,9410.84,-6856.04,14.8094,5.30187,0,0,0.471204,-0.882024,300,0,1),
(@GUID+17,195087,1,1,1,10051.5,2108.48,1329.65,5.63954,0,0,0.316296,-0.948661,300,0,1),
(@GUID+18,195087,1,1,1,-978.502,-68.0701,19.8816,2.48265,0,0,0.946214,0.323543,300,0,1),
(@GUID+19,195087,530,1,1,-4320.88,-12435.8,17.794,2.95615,0,0,0.995704,0.0925905,300,0,1),
(@GUID+20,195087,530,1,1,-1795.3,4913.74,-21.6189,5.79582,0,0,0.241278,-0.970456,300,0,1),
(@GUID+21,195087,0,1,1,-5167.15,-868.97,506.692,3.55298,0,0,0.97892,-0.204245,300,0,1),
(@GUID+22,195067,571,1,65535,5842.99,757.208,641.032,3.23312,0,0,0.998953,-0.0457468,300,0,1),
(@GUID+23,195067,571,1,65535,5848.67,757.932,640.765,0.331072,0,0,0.164781,0.98633,300,0,1),
(@GUID+24,195067,571,1,65535,5826.98,742.899,642.182,0.40961,0,0,0.203376,0.979101,300,0,1),
(@GUID+25,195067,571,1,65535,5833.05,758.772,640.632,6.22548,0,0,0.0288469,-0.999584,300,0,1),
(@GUID+26,195067,571,1,65535,5838.49,754.714,640.99,5.00419,0,0,0.596791,-0.802397,300,0,1),
(@GUID+27,195067,0,1,1,-9325.85,176.738,61.6842,4.03415,0,0,0.902059,-0.431613,300,0,1),
(@GUID+28,195067,0,1,1,-9339.4,177.75,61.5578,2.84035,0,0,0.988678,0.150053,300,0,1),
(@GUID+29,195067,0,1,1,-9341.6,186.007,61.5588,0.590182,0,0,0.290827,0.956776,300,0,1),
(@GUID+30,195067,0,1,1,-9349.4,172.027,61.5583,3.72,0,0,0.958472,-0.285187,300,0,1),
(@GUID+31,195067,0,1,1,-9333.49,166.771,61.5731,4.50147,0,0,0.777611,-0.628745,300,0,1),
(@GUID+32,195067,0,1,1,1838.15,218.056,60.1301,6.04382,0,0,0.119397,-0.992847,300,0,1),
(@GUID+33,195067,0,1,1,1824.56,214.048,60.2184,2.55272,0,0,0.956966,0.290199,300,0,1),
(@GUID+34,195067,0,1,1,1826.85,224.597,60.3819,1.15864,0,0,0.547456,0.836835,300,0,1),
(@GUID+35,195067,0,1,1,1834.25,227.476,60.3832,0.0394494,0,0,0.0197234,0.999805,300,0,1),
(@GUID+36,195067,530,1,1,9408.5,-6861.43,14.8097,5.18014,0,0,0.523987,-0.851727,300,0,1),
(@GUID+37,195067,530,1,1,9414.83,-6847.96,15.2124,0.302815,0,0,0.15083,0.98856,300,0,1),
(@GUID+38,195067,530,1,1,9406.18,-6848.78,15.7346,4.10414,0,0,0.886406,-0.462909,300,0,1),
(@GUID+39,195067,1,1,1,10040.1,2118.35,1329.71,6.16969,0,0,0.0567171,-0.99839,300,0,1),
(@GUID+40,195067,1,1,1,10054.5,2128.79,1329.66,0.15354,0,0,0.0766945,0.997055,300,0,1),
(@GUID+41,195067,1,1,1,10064.3,2124.92,1329.66,5.938,0,0,0.171738,-0.985143,300,0,1),
(@GUID+42,195067,1,1,1,10048.2,2118.42,1329.87,6.00475,0,0,0.138768,-0.990325,300,0,1),
(@GUID+43,195067,1,1,1,-981.572,-70.544,20.3174,2.24703,0,0,0.901626,0.432516,300,0,1),
(@GUID+44,195067,1,1,1,-982.861,-78.1374,20.4409,2.76147,0,0,0.981992,0.188921,300,0,1),
(@GUID+45,195067,1,1,1,-979.741,-82.5911,20.4482,2.84001,0,0,0.988652,0.150222,300,0,1),
(@GUID+46,195067,1,1,1,-985.891,-59.0171,27.1512,2.98923,0,0,0.9971,0.0761065,300,0,1),
(@GUID+47,195067,530,1,1,-4330.57,-12441.9,18.6116,1.10261,0,0,0.523798,0.851843,300,0,1),
(@GUID+48,195067,530,1,1,-4331.79,-12444.3,18.6116,1.10261,0,0,0.523798,0.851843,300,0,1),
(@GUID+49,195067,530,1,1,-4320.15,-12431.6,18.6801,3.86328,0,0,0.935599,-0.353065,300,0,1),
(@GUID+50,195067,530,1,1,-4318.44,-12430.1,18.6801,3.84757,0,0,0.938343,-0.345706,300,0,1),
(@GUID+51,195067,530,1,1,-4322.19,-12440.2,17.4944,3.02291,0,0,0.99824,0.0593089,300,0,1),
(@GUID+52,195067,530,1,1,-4323.07,-12450.7,16.8485,5.33983,0,0,0.454382,-0.890807,300,0,1),
(@GUID+53,195067,530,1,1,-4311.45,-12442.3,17.3037,0.772738,0,0,0.376827,0.926284,300,0,1),
(@GUID+54,195067,530,1,1,-1791.77,4917.77,-21.025,1.42901,0,0,0.655244,0.755417,300,0,1),
(@GUID+55,195067,530,1,1,-1789.47,4922.28,-21.0992,1.01275,0,0,0.48501,0.874508,300,0,1),
(@GUID+56,195067,530,1,1,-1784.66,4926.07,-21.1388,0.521876,0,0,0.257987,0.966148,300,0,1),
(@GUID+57,195067,530,1,1,-1799.03,4911.63,-21.3716,4.9201,0,0,0.62999,-0.776603,300,0,1),
(@GUID+58,195067,530,1,1,-1811.06,4914.83,-21.8399,3.80091,0,0,0.946153,-0.32372,300,0,1),
(@GUID+59,195067,530,1,1,-1804.87,4922.87,-21.9285,0.341232,0,0,0.169789,0.98548,300,0,1),
(@GUID+60,195067,0,1,1,-5157.02,-875.2,507.717,5.59108,0,0,0.339185,-0.94072,300,0,1),
(@GUID+61,195067,0,1,1,-5162.53,-877.151,507.269,3.8475,0,0,0.938356,-0.345672,300,0,1),
(@GUID+62,195067,0,1,1,-5168.31,-872.67,506.918,4.71929,0,0,0.704662,-0.709544,300,0,1),
(@GUID+63,195067,0,1,1,-5159.9,-868.605,507.293,4.7782,0,0,0.683461,-0.729987,300,0,1),
(@GUID+64,195067,0,1,1,-5153.67,-856.503,508.317,1.38528,0,0,0.63857,0.769564,300,0,1),
(@GUID+65,195090,0,1,1,-5153.07,-855.424,508.469,2.04894,0,0,0.854438,0.519553,300,0,1),
(@GUID+66,195090,1,1,1,1187.46,-4465.48,21.3276,5.08777,0,0,0.562749,-0.826628,300,0,1),
(@GUID+67,195090,1,1,1,1184.69,-4469.05,21.3202,3.92145,0,0,0.924935,-0.380125,300,0,1),
(@GUID+68,195090,1,1,1,1178.71,-4465.61,21.3464,2.50381,0,0,0.949584,0.313514,300,0,1),
(@GUID+69,195090,1,1,1,1173.45,-4463.9,21.2566,2.95934,0,0,0.995851,0.0909994,300,0,1),
(@GUID+70,195090,1,1,1,1174.56,-4459.12,21.5159,1.31393,0,0,0.610717,0.791849,300,0,1),
(@GUID+71,195090,1,1,1,1178.38,-4459.37,21.4634,6.03418,0,0,0.124183,-0.992259,300,0,1),
(@GUID+72,195090,1,1,1,1183.11,-4462.38,21.173,0.457849,0,0,0.22693,0.973911,300,0,1),
(@GUID+73,195090,0,1,1,-9319.35,175.184,61.6322,5.94267,0,0,0.169436,-0.985541,300,0,1),
(@GUID+74,195090,0,1,1,-9321.89,177.068,61.6465,5.64422,0,0,0.314075,-0.949398,300,0,1),
(@GUID+75,195090,0,1,1,-9324.42,178.952,61.9249,5.64422,0,0,0.314075,-0.949398,300,0,1),
(@GUID+76,195090,0,1,1,-9327.35,181.579,61.6579,5.76203,0,0,0.257639,-0.966241,300,0,1),
(@GUID+77,195090,0,1,1,-9329.68,183.137,61.6151,5.69527,0,0,0.289742,-0.957105,300,0,1),
(@GUID+78,195090,0,1,1,-9332.5,185.014,61.5442,5.69527,0,0,0.289742,-0.957105,300,0,1),
(@GUID+79,195090,0,1,1,-9336.77,184.723,61.5328,1.08891,0,0,0.517952,0.85541,300,0,1),
(@GUID+80,195090,0,1,1,-9340.96,187.22,61.5554,0.865071,0,0,0.419174,0.907906,300,0,1),
(@GUID+81,195090,0,1,1,-9347.4,178.086,61.558,4.29726,0,0,0.837647,-0.546212,300,0,1),
(@GUID+82,195090,0,1,1,-9349.37,175.371,61.7816,4.06557,0,0,0.895168,-0.445729,300,0,1),
(@GUID+83,195090,0,1,1,-9351.22,172.514,61.5657,4.2737,0,0,0.844024,-0.536305,300,0,1),
(@GUID+84,195090,0,1,1,-9352.79,169.484,61.5833,4.19909,0,0,0.86344,-0.504452,300,0,1),
(@GUID+85,195090,0,1,1,-9328.38,163.069,62.1162,5.656,0,0,0.308476,-0.951232,300,0,1),
(@GUID+86,195090,0,1,1,-9324.64,167.678,61.5815,2.66756,0,0,0.972043,0.234801,300,0,1),
(@GUID+87,195090,0,1,1,-9327.99,170.234,61.6257,2.49478,0,0,0.948158,0.317799,300,0,1),
(@GUID+88,195090,0,1,1,-9330.76,172.21,61.6444,2.42016,0,0,0.935645,0.352943,300,0,1),
(@GUID+89,195090,0,1,1,-9333.31,174.06,61.6475,2.60866,0,0,0.964707,0.263324,300,0,1),
(@GUID+90,195090,0,1,1,-9335.44,175.283,61.6076,2.62044,0,0,0.966242,0.257637,300,0,1),
(@GUID+91,195090,0,1,1,-9329.47,179.114,61.7075,1.27741,0,0,0.596156,0.802868,300,0,1),
(@GUID+92,195090,571,1,65535,5853.87,762.992,641.211,6.18229,0,0,0.0504241,-0.998728,300,0,1),
(@GUID+93,195090,571,1,65535,5855.51,765.516,641.483,0.212483,0,0,0.106042,0.994362,300,0,1),
(@GUID+94,195090,571,1,65535,5853.92,767.065,641.349,0.656233,0,0,0.322261,0.946651,300,0,1),
(@GUID+95,195090,571,1,65535,5851.19,767.209,640.997,0.597328,0,0,0.294244,0.95573,300,0,1),
(@GUID+96,195090,571,1,65535,5851.3,769.624,640.886,1.09213,0,0,0.519328,0.854575,300,0,1),
(@GUID+97,195090,571,1,65535,5849.36,771.084,640.573,1.31204,0,0,0.609968,0.792426,300,0,1),
(@GUID+98,195090,571,1,65535,5843.35,763.212,640.647,3.49938,0,0,0.984042,-0.177939,300,0,1),
(@GUID+99,195090,571,1,65535,5832.79,754.608,640.935,4.05308,0,0,0.897934,-0.440131,300,0,1),
(@GUID+100,195090,571,1,65535,5828.7,749.25,641.164,4.17874,0,0,0.868526,-0.495643,300,0,1),
(@GUID+101,195090,571,1,65535,5835.35,751.259,641.084,0.400976,0,0,0.199148,0.97997,300,0,1),
(@GUID+102,195090,571,1,65535,5827.74,742.946,642.332,0.687646,0,0,0.337089,0.941473,300,0,1),
(@GUID+103,195090,571,1,65535,5809.37,743.705,640.998,3.12238,0,0,0.999954,0.00960593,300,0,1),
(@GUID+104,195090,571,1,65535,5822.29,758.23,640.365,1.61049,0,0,0.721,0.692935,300,0,1),
(@GUID+105,195090,571,1,65535,5811.39,757.19,640.324,2.50977,0,0,0.950514,0.310683,300,0,1),
(@GUID+106,195090,571,1,65535,5846.75,758.117,640.939,6.14616,0,0,0.0684576,-0.997654,300,0,1),
(@GUID+107,195090,0,1,1,1830.63,211.165,60.3098,4.80682,0,0,0.672944,-0.739693,300,0,1),
(@GUID+108,195090,0,1,1,1840.85,213.082,61.3837,5.26628,0,0,0.486826,-0.873499,300,0,1),
(@GUID+109,195090,0,1,1,1841.8,219.772,60.7409,1.28038,0,0,0.597349,0.801981,300,0,1),
(@GUID+110,195090,0,1,1,1823.03,229.093,60.4377,2.72944,0,0,0.978842,0.204619,300,0,1),
(@GUID+111,195090,0,1,1,1827.77,222.032,60.6016,4.97961,0,0,0.60661,-0.795,300,0,1),
(@GUID+112,195090,0,1,1,1827.52,217.594,60.5054,4.65367,0,0,0.72756,-0.686044,300,0,1),
(@GUID+113,195090,0,1,1,1832.1,217.303,60.342,6.21268,0,0,0.0352447,-0.999379,300,0,1),
(@GUID+114,195090,0,1,1,1834.79,220.5,60.2436,1.11937,0,0,0.530921,0.847421,300,0,1),
(@GUID+115,195090,0,1,1,1814.67,217.597,60.2211,3.50306,0,0,0.983712,-0.17975,300,0,1),
(@GUID+116,195090,530,1,1,9407.83,-6850.31,15.4148,6.05585,0,0,0.113421,-0.993547,300,0,1),
(@GUID+117,195090,530,1,1,9412.52,-6848.4,15.3197,0.703365,0,0,0.344478,0.938794,300,0,1),
(@GUID+118,195090,530,1,1,9414.82,-6851.42,15.0296,5.58069,0,0,0.344071,-0.938944,300,0,1),
(@GUID+119,195090,530,1,1,9410.57,-6853.66,14.9713,3.57007,0,0,0.977139,-0.212602,300,0,1),
(@GUID+120,195090,530,1,1,9405.72,-6861.46,14.9588,4.79136,0,0,0.678642,-0.734469,300,0,1),
(@GUID+121,195090,530,1,1,9412.52,-6861.73,14.6487,5.88699,0,0,0.196805,-0.980443,300,0,1),
(@GUID+122,195090,530,1,1,9416.75,-6856.38,14.8519,5.80845,0,0,0.235147,-0.97196,300,0,1),
(@GUID+123,195090,530,1,1,9418.64,-6852.18,14.9737,5.72205,0,0,0.2769,-0.960899,300,0,1),
(@GUID+124,195090,1,1,1,10062.7,2128.29,1329.77,1.94816,0,0,0.827186,0.561928,300,0,1),
(@GUID+125,195090,1,1,1,10066.2,2127.23,1329.66,4.62637,0,0,0.736856,-0.67605,300,0,1),
(@GUID+126,195090,1,1,1,10065.9,2121.66,1330.2,4.78738,0,0,0.680104,-0.733115,300,0,1),
(@GUID+127,195090,1,1,1,10064.8,2117.6,1330.03,4.56746,0,0,0.756445,-0.654057,300,0,1),
(@GUID+128,195090,1,1,1,10063.4,2113.77,1330.06,4.01769,0,0,0.905582,-0.424171,300,0,1),
(@GUID+129,195090,1,1,1,10054.1,2110.63,1329.93,3.8449,0,0,0.938805,-0.344449,300,0,1),
(@GUID+130,195090,1,1,1,10049.1,2112.98,1330.03,2.00314,0,0,0.842318,0.538981,300,0,1),
(@GUID+131,195090,1,1,1,10046.4,2109.25,1329.96,4.10408,0,0,0.88642,-0.462882,300,0,1),
(@GUID+132,195090,1,1,1,10053.1,2126.22,1330.07,1.08422,0,0,0.515946,0.856621,300,0,1),
(@GUID+133,195090,1,1,1,10054,2130.84,1330.02,1.00961,0,0,0.483637,0.875269,300,0,1),
(@GUID+134,195090,1,1,1,10060.3,2124.09,1330.01,4.74418,0,0,0.695778,-0.718257,300,0,1),
(@GUID+135,195090,1,1,1,10059.9,2135.05,1330.75,1.53583,0,0,0.694637,0.719361,300,0,1),
(@GUID+136,195090,1,1,1,10066.4,2132.16,1332.09,2.49402,0,0,0.948037,0.31816,300,0,1),
(@GUID+137,195090,1,1,1,10052.2,2104.91,1330.92,3.28727,0,0,0.997349,-0.0727721,300,0,1),
(@GUID+138,195090,1,1,1,-988.152,-59.1082,27.5232,5.15851,0,0,0.533167,-0.84601,300,0,1),
(@GUID+139,195090,1,1,1,-977.555,-56.5706,26.7082,5.00143,0,0,0.5979,-0.801571,300,0,1),
(@GUID+140,195090,1,1,1,-979.763,-72.5159,19.6852,3.24999,0,0,0.998531,-0.0541744,300,0,1),
(@GUID+141,195090,1,1,1,-979.359,-76.7106,19.6107,3.13611,0,0,0.999996,0.00274046,300,0,1),
(@GUID+142,195090,1,1,1,-976.6,-74.4185,18.8465,3.47776,0,0,0.985907,-0.167293,300,0,1),
(@GUID+143,195090,1,1,1,-981.652,-79.1964,20.249,3.91758,0,0,0.925669,-0.378334,300,0,1),
(@GUID+144,195090,1,1,1,-985.178,-75.001,21.0173,3.12433,0,0,0.999963,0.00863036,300,0,1),
(@GUID+145,195090,1,1,1,-981.153,-66.7737,20.9042,2.28788,0,0,0.910272,0.41401,300,0,1),
(@GUID+146,195090,530,1,1,-4319.45,-12430.9,18.6806,2.09613,0,0,0.866459,0.499248,300,0,1),
(@GUID+147,195090,530,1,1,-4320.99,-12432.3,18.6806,3.9536,0,0,0.918707,-0.394941,300,0,1),
(@GUID+148,195090,530,1,1,-4331.11,-12443.6,18.6114,2.34746,0,0,0.922199,0.386715,300,0,1),
(@GUID+149,195090,530,1,1,-4325.9,-12451.6,16.6623,0.839496,0,0,0.40753,0.913192,300,0,1),
(@GUID+150,195090,530,1,1,-4326.17,-12455.4,16.9729,0.509629,0,0,0.252066,0.96771,300,0,1),
(@GUID+151,195090,530,1,1,-4320.52,-12456.9,17.3025,0.721686,0,0,0.353063,0.9356,300,0,1),
(@GUID+152,195090,530,1,1,-4321.35,-12454.2,17.2013,0.914109,0,0,0.441307,0.897356,300,0,1),
(@GUID+153,195090,530,1,1,-4320.01,-12449.5,17.0817,0.800226,0,0,0.389522,0.921017,300,0,1),
(@GUID+154,195090,530,1,1,-4314.66,-12447.8,17.3873,1.00836,0,0,0.483088,0.875572,300,0,1),
(@GUID+155,195090,530,1,1,-4311.21,-12446.3,17.4275,1.0869,0,0,0.51709,0.855931,300,0,1),
(@GUID+156,195090,530,1,1,-4316.32,-12444.3,17.1922,0.88662,0,0,0.428932,0.903337,300,0,1),
(@GUID+157,195090,530,1,1,-4310.89,-12440.6,17.2147,1.05941,0,0,0.505278,0.862957,300,0,1),
(@GUID+158,195090,530,1,1,-1801.49,4910.65,-21.3903,5.6034,0,0,0.333386,-0.94279,300,0,1),
(@GUID+159,195090,530,1,1,-1796.61,4911.2,-21.382,0.113465,0,0,0.0567022,0.998391,300,0,1),
(@GUID+160,195090,530,1,1,-1792.12,4916.53,-21.0244,1.24837,0,0,0.584434,0.811441,300,0,1),
(@GUID+161,195090,530,1,1,-1788.82,4923.25,-21.0863,1.01275,0,0,0.485009,0.874509,300,0,1),
(@GUID+162,195090,530,1,1,-1786.08,4925.63,-21.1386,0.243056,0,0,0.121229,0.992625,300,0,1),
(@GUID+163,195090,530,1,1,-1806.29,4914.21,-22.0573,3.90301,0,0,0.928401,-0.371579,300,0,1),
(@GUID+164,195090,530,1,1,-1814.82,4912.82,-21.4843,3.71452,0,0,0.95925,-0.28256,300,0,1),
(@GUID+165,195090,530,1,1,-1808.63,4922.35,-21.8564,1.05594,0,0,0.503782,0.863831,300,0,1),
(@GUID+166,195090,530,1,1,-1810.52,4926.39,-21.734,1.05202,0,0,0.502085,0.864818,300,0,1),
(@GUID+167,195090,530,1,1,-1812.06,4920.92,-21.9526,0.945987,0,0,0.455553,0.890209,300,0,1),
(@GUID+168,195090,530,1,1,-1795.43,4927.2,-22.1493,0.270544,0,0,0.13486,0.990865,300,0,1),
(@GUID+169,195090,530,1,1,-1796.32,4931.29,-22.3174,0.129173,0,0,0.0645415,0.997915,300,0,1),
(@GUID+170,195090,530,1,1,-1799.12,4928.21,-22.2813,0.707226,0,0,0.346289,0.938128,300,0,1),
(@GUID+171,195090,530,1,1,-1783.82,4935.44,-22.5892,5.4471,0,0,0.405971,-0.913886,300,0,1),
(@GUID+172,195090,530,1,1,-1829.25,4920.79,-21.671,4.42216,0,0,0.801927,-0.597422,300,0,1),
(@GUID+173,195090,530,1,1,-1835.24,4924,-21.3785,4.00983,0,0,0.907242,-0.420609,300,0,1),
(@GUID+174,195090,530,1,1,-1798.26,4902.69,-21.4127,5.45889,0,0,0.400579,-0.916262,300,0,1),
(@GUID+175,195090,530,1,1,-1792.22,4911.42,-21.4162,5.16829,0,0,0.529021,-0.848609,300,0,1),
(@GUID+176,195090,0,1,1,-5146.92,-846.795,509.814,4.73578,0,0,0.698788,-0.715329,300,0,1),
(@GUID+177,195090,0,1,1,-5148.88,-848.813,510.175,3.96217,0,0,0.917006,-0.398873,300,0,1),
(@GUID+178,195090,0,1,1,-5154.23,-851.792,509.604,3.80116,0,0,0.946112,-0.323839,300,0,1),
(@GUID+179,195090,0,1,1,-5151.12,-850.78,510.203,2.82334,0,0,0.987366,0.158455,300,0,1),
(@GUID+180,195090,0,1,1,-5157.25,-865.505,507.488,4.03286,0,0,0.902338,-0.431029,300,0,1),
(@GUID+181,195090,0,1,1,-5162.21,-871.414,507.192,3.93861,0,0,0.921641,-0.388044,300,0,1),
(@GUID+182,195090,0,1,1,-5158.06,-875.801,507.508,4.08391,0,0,0.891043,-0.453918,300,0,1),
(@GUID+183,195090,0,1,1,-5163.62,-875.984,507.254,4.18994,0,0,0.865739,-0.500496,300,0,1),
(@GUID+184,195090,0,1,1,-5166.94,-874.019,507.083,2.13612,0,0,0.876268,0.481825,300,0,1),
(@GUID+185,195090,0,1,1,-5166.83,-871.411,506.884,1.14652,0,0,0.542373,0.840138,300,0,1),
(@GUID+186,195090,0,1,1,-5164.94,-867.229,506.913,1.14652,0,0,0.542373,0.840138,300,0,1),
(@GUID+187,195090,0,1,1,-5167.77,-861.231,506.701,0.420025,0,0,0.208472,0.978028,300,0,1),
(@GUID+188,195090,0,1,1,-5165.58,-860.107,506.446,0.475003,0,0,0.235275,0.971929,300,0,1),
(@GUID+189,195090,0,1,1,-5163.08,-858.823,506.659,0.475003,0,0,0.235275,0.971929,300,0,1),
(@GUID+190,195090,0,1,1,-5160.59,-857.539,506.642,0.475003,0,0,0.235275,0.971929,300,0,1),
(@GUID+191,195090,0,1,1,-5157.78,-856.092,507.248,0.475003,0,0,0.235275,0.971929,300,0,1),
(@GUID+192,195307,1,1,1,10054.6,2131.96,1329.66,-2.75761,0,0,0,1,180,100,1),
(@GUID+193,195307,1,1,1,10062.8,2129.42,1329.66,-2.30383,0,0,0,1,180,100,1),
(@GUID+194,195307,0,1,1,-5159.66,-869.708,507.315,3.00195,0,0,0,1,180,100,1),
(@GUID+195,195307,0,1,1,-5160.8,-869.684,507.251,-2.30383,0,0,0,1,180,100,1),
(@GUID+196,195307,0,1,1,-9328.34,171.941,62.8343,3.00195,0,0,0,1,180,100,1),
(@GUID+197,195307,0,1,1,-9351.13,177.262,62.7149,-2.30383,0,0,0,1,180,100,1),
(@GUID+198,195307,1,1,1,1171.94,-4462.66,21.3171,3.00195,0,0,0,1,180,100,1),
(@GUID+199,195307,1,1,1,1177.22,-4464.5,22.4542,-2.30383,0,0,0,1,180,100,1),
(@GUID+200,195307,1,1,1,-984.535,-75.8281,20.8642,3.00195,0,0,0,1,180,100,1),
(@GUID+201,195307,1,1,1,-979.977,-71.342,20.7172,-2.30383,0,0,0,1,180,100,1),
(@GUID+202,195068,0,1,1,1780.14,269.759,59.8725,0,0,0,0,1,180,100,1),
(@GUID+203,195068,0,1,1,1777.31,220.538,59.5768,0,0,0,0,1,180,100,1),
(@GUID+204,195068,1,1,1,10053.6,2109.59,1329.65,0,0,0,0,1,180,100,1),
(@GUID+205,195068,1,1,1,10065,2118.72,1329.66,0,0,0,0,1,180,100,1),
(@GUID+206,195068,1,1,1,10053.4,2128.55,1329.66,0,0,0,0,1,180,100,1),
(@GUID+207,195068,0,1,1,-5160.02,-869.03,507.29,0,0,0,0,1,180,100,1),
(@GUID+208,195068,0,1,1,-5159.92,-870.566,507.307,0,0,0,0,1,180,100,1),
(@GUID+209,195068,0,1,1,-9328.37,170.188,61.6268,0,0,0,0,1,180,100,1),
(@GUID+210,195068,0,1,1,-9327.13,181.863,61.6551,0,0,0,0,1,180,100,1),
(@GUID+211,195068,1,1,1,1180.13,-4457.48,21.4889,0,0,0,0,1,180,100,1),
(@GUID+212,195068,1,1,1,1186.07,-4471.15,21.3707,0,0,0,0,1,180,100,1),
(@GUID+213,195068,1,1,1,1172.28,-4463.25,21.2866,0,0,0,0,1,180,100,1),
(@GUID+214,195068,1,1,1,-983.009,-70.0955,20.7835,0,0,0,0,1,180,100,1),
(@GUID+215,195068,1,1,1,-984.639,-76.1319,20.8549,0,0,0,0,1,180,100,1),
(@GUID+216,195068,1,1,1,-984.92,-75.1719,20.9388,0,0,0,0,1,180,100,1),
(@GUID+217,195067,0,1,1,1778.85,260.073,59.498,0,0,0,0,1,180,100,1),
(@GUID+218,195067,1,1,1,10054.1,2124.82,1329.7,0,0,0,0,1,180,100,1),
(@GUID+219,195067,1,1,1,10047.4,2110.17,1329.65,0,0,0,0,1,180,100,1),
(@GUID+220,195067,1,1,1,10059.8,2122.52,1329.67,0,0,0,0,1,180,100,1),
(@GUID+221,195067,0,1,1,-5161.69,-869.67,507.202,0,0,0,0,1,180,100,1),
(@GUID+222,195067,0,1,1,-9352.43,172.927,61.5748,0,0,0,0,1,180,100,1),
(@GUID+223,195067,1,1,1,1175.47,-4455.32,21.5219,0,0,0,0,1,180,100,1),
(@GUID+224,195067,1,1,1,1185.36,-4460.86,21.102,0,0,0,0,1,180,100,1),
(@GUID+225,195067,1,1,1,1179.27,-4468.45,21.2471,0,0,0,0,1,180,100,1),
(@GUID+226,195067,1,1,1,-983.566,-73.3247,20.6424,0,0,0,0,1,180,100,1),
(@GUID+227,195067,1,1,1,-980.892,-79.2656,20.1022,0,0,0,0,1,180,100,1),
(@GUID+228,195063,1,1,1,1191.1,-4465.38,21.489,0,0,0,0,1,180,100,1),
(@GUID+229,195063,1,1,1,1176.06,-4456.3,21.5271,0,0,0,0,1,180,100,1),
(@GUID+230,195063,1,1,1,1185.15,-4469.57,21.3318,0,0,0,0,1,180,100,1),
(@GUID+231,195063,0,1,1,1776.75,250.743,59.8824,0,0,0,0,1,180,100,1),
(@GUID+232,195063,0,1,1,1782.6,260.549,59.42,0,0,0,0,1,180,100,1),
(@GUID+233,195063,0,1,1,1776.35,223.174,59.5078,0,0,0,0,1,180,100,1),
(@GUID+234,195063,0,1,1,1781.6,252.318,59.5262,0,0,0,0,1,180,100,1),
(@GUID+235,195063,0,1,1,1779.51,268.924,59.893,0,0,0,0,1,180,100,1),
(@GUID+236,195063,1,1,1,10066.4,2120.48,1329.66,0,0,0,0,1,180,100,1),
(@GUID+237,195063,1,1,1,10046.7,2110.08,1329.65,0,0,0,0,1,180,100,1),
(@GUID+238,195063,1,1,1,10050.3,2118.57,1331.05,0,0,0,0,1,180,100,1),
(@GUID+239,195063,1,1,1,10063.6,2112.16,1329.66,0,0,0,0,1,180,100,1),
(@GUID+240,195063,1,1,1,10055,2111.28,1329.65,0,0,0,0,1,180,100,1),
(@GUID+241,195063,0,1,1,-5158.94,-869.955,507.357,0,0,0,0,1,180,100,1),
(@GUID+242,195063,0,1,1,-5160.05,-871.753,507.315,0,0,0,0,1,180,100,1),
(@GUID+243,195063,0,1,1,-5161.04,-868.969,507.233,0,0,0,0,1,180,100,1),
(@GUID+244,195063,0,1,1,-5149.86,-882.234,508.225,0,0,0,0,1,180,100,1),
(@GUID+245,195063,0,1,1,-5162.1,-870.601,507.185,0,0,0,0,1,180,100,1),
(@GUID+246,195063,0,1,1,-5149.59,-854.429,509.499,0,0,0,0,1,180,100,1),
(@GUID+247,195063,0,1,1,-9323.89,179.863,64.6421,0,0,0,0,1,180,100,1),
(@GUID+248,195063,0,1,1,-9330.93,172.332,61.6442,0,0,0,0,1,180,100,1),
(@GUID+249,195063,0,1,1,-9331.52,182.493,61.6,0,0,0,0,1,180,100,1),
(@GUID+250,195063,0,1,1,-9334.96,176.014,63.3874,0,0,0,0,1,180,100,1),
(@GUID+251,195063,0,1,1,-9340.66,187.524,61.5517,0,0,0,0,1,180,100,1),
(@GUID+252,195063,1,1,1,1176.77,-4463.59,22.4735,0,0,0,0,1,180,100,1),
(@GUID+253,195063,1,1,1,1177.63,-4467.96,21.307,0,0,0,0,1,180,100,1),
(@GUID+254,195063,1,1,1,1174.72,-4455.49,21.5368,0,0,0,0,1,180,100,1),
(@GUID+255,195063,1,1,1,-980.41,-71.3438,20.7185,0,0,0,0,1,180,100,1),
(@GUID+256,195063,1,1,1,-983.493,-72.6302,20.6698,0,0,0,0,1,180,100,1),
(@GUID+257,195063,1,1,1,-982.13,-68.0764,20.8836,0,0,0,0,1,180,100,1),
(@GUID+258,195063,1,1,1,-984.149,-77.3333,20.7527,0,0,0,0,1,180,100,1),
(@GUID+259,195063,1,1,1,-980.212,-80.2552,20.0676,0,0,0,0,1,180,100,1),
(@GUID+260,182807,1,1,1,1184.02,-4469.83,21.2852,0,0,0,0,1,180,100,1),
(@GUID+261,182807,530,1,1,9672.12,-7346.44,11.9311,-0.244346,0,0,0.121869,-0.992546,180,100,1),
(@GUID+262,182807,0,1,1,1780.18,214.781,59.8534,0,0,0,0,1,180,100,1),
(@GUID+263,182807,0,1,1,1780.76,215.611,59.7988,0,0,0,0,1,180,100,1),
(@GUID+264,182807,1,1,1,10063.4,2111.85,1329.66,0,0,0,0,1,180,100,1),
(@GUID+265,182807,1,1,1,10062.7,2129.98,1329.66,0,0,0,0,1,180,100,1),
(@GUID+266,182807,1,1,1,10065.5,2118.46,1329.66,0,0,0,0,1,180,100,1),
(@GUID+267,182807,1,1,1,10054.8,2132.24,1329.66,0,0,0,0,1,180,100,1),
(@GUID+268,182807,1,1,1,10053.7,2125.31,1329.69,0,0,0,0,1,180,100,1),
(@GUID+269,182807,0,1,1,-5161.27,-870.734,507.233,0,0,0,0,1,180,100,1),
(@GUID+270,182807,0,1,1,-5160.73,-871.283,507.27,0,0,0,0,1,180,100,1),
(@GUID+271,182807,0,1,1,-9326.85,170.807,62.8254,0,0,0,0,1,180,100,1),
(@GUID+272,182807,0,1,1,-9335.46,175.405,61.6072,0,0,0,0,1,180,100,1),
(@GUID+273,182807,1,1,1,1174.36,-4455.34,21.5514,0,0,0,0,1,180,100,1),
(@GUID+274,182807,1,1,1,-984.738,-73.1875,20.9946,0,0,0,0,1,180,100,1),
(@GUID+275,182807,1,1,1,-980.771,-79.8229,20.1335,0,0,0,0,1,180,100,1),
(@GUID+276,180885,0,1,1,1805.89,217.134,60.6002,1.51844,0,0,0,1,180,100,1),
(@GUID+277,180885,1,1,1,10050.3,2118.06,1329.94,0.750491,0,0,0,1,180,100,1),
(@GUID+278,180885,0,1,1,-5149.52,-854.931,508.432,0.750491,0,0,0,1,180,100,1),
(@GUID+279,180885,0,1,1,-9331.44,181.991,61.63,0.750491,0,0,0,1,180,100,1),
(@GUID+280,180885,1,1,1,1176.85,-4464.09,21.3468,0.750491,0,0,0,1,180,100,1),
(@GUID+281,180885,1,1,1,-980.33,-71.8455,19.5878,0.750491,0,0,0,1,180,100,1),
(@GUID+282,195066,0,1,1,-9328.34,170.201,61.6675,0,0,0,0,1,180,100,1),
(@GUID+283,195069,0,1,1,-9331.48,181.45,62.7343,-0.890117,0,0,0,1,180,100,1),
(@GUID+284,195069,0,1,1,-9332.01,182.043,62.6892,-0.157079,0,0,0,1,180,100,1),
(@GUID+285,195066,0,1,1,-9327.13,181.875,61.6549,0,0,0,0,1,180,100,1),
(@GUID+286,195069,0,1,1,-5149.05,-855.003,509.504,2.54818,0,0,0,1,180,100,1),
(@GUID+287,195069,0,1,1,-5149.55,-855.472,509.469,-0.890117,0,0,0,1,180,100,1),
(@GUID+288,195069,0,1,1,-5150.07,-854.878,509.496,-0.157079,0,0,0,1,180,100,1),
(@GUID+289,195066,0,1,1,-5159.99,-869.016,507.291,0,0,0,0,1,180,100,1),
(@GUID+290,195066,0,1,1,-5159.91,-870.554,507.307,0,0,0,0,1,180,100,1),
(@GUID+291,195069,1,1,1,10049.8,2118.11,1331.01,-0.157079,0,0,0,1,180,100,1),
(@GUID+292,195069,1,1,1,10050.9,2117.89,1331.03,1.72787,0,0,0,1,180,100,1),
(@GUID+293,195066,1,1,1,10065.1,2118.72,1329.66,0,0,0,0,1,180,100,1),
(@GUID+294,195066,1,1,1,10053.5,2128.55,1329.66,0,0,0,0,1,180,100,1),
(@GUID+295,195069,1,1,1,10050.3,2117.48,1330.99,-0.890117,0,0,0,1,180,100,1),
(@GUID+296,195066,1,1,1,10053.6,2109.59,1329.65,0,0,0,0,1,180,100,1),
(@GUID+297,195066,0,1,1,1777.32,220.55,59.5767,0,0,0,0,1,180,100,1),
(@GUID+298,195066,0,1,1,1780.16,269.773,59.8725,0,0,0,0,1,180,100,1),
(@GUID+299,195069,0,1,1,1805.33,217.408,61.5327,-0.157079,0,0,0,1,180,100,1),
(@GUID+300,195069,0,1,1,1805.86,216.814,61.5886,-0.890117,0,0,0,1,180,100,1),
(@GUID+301,195069,0,1,1,1806.35,217.283,61.5437,2.54818,0,0,0,1,180,100,1),
(@GUID+302,195066,1,1,1,1186.07,-4471.14,21.3708,0,0,0,0,1,180,100,1),
(@GUID+303,195066,1,1,1,1180.13,-4457.47,21.4891,0,0,0,0,1,180,100,1),
(@GUID+304,195069,1,1,1,1176.29,-4464.04,22.4501,-0.157079,0,0,0,1,180,100,1),
(@GUID+305,195066,1,1,1,1172.31,-4463.23,21.2882,0,0,0,0,1,180,100,1),
(@GUID+306,195069,1,1,1,1177.32,-4464.16,22.4611,2.54818,0,0,0,1,180,100,1),
(@GUID+307,195069,1,1,1,1176.82,-4464.63,22.4507,-0.890117,0,0,0,1,180,100,1),
(@GUID+308,195066,1,1,1,-984.632,-76.1215,20.8542,0,0,0,0,1,180,100,1),
(@GUID+309,195069,1,1,1,-979.866,-71.9184,20.7017,2.54818,0,0,0,1,180,100,1),
(@GUID+310,195066,1,1,1,-983.002,-70.0833,20.7837,0,0,0,0,1,180,100,1),
(@GUID+311,195066,1,1,1,-984.913,-75.1597,20.9375,0,0,0,0,1,180,100,1),
(@GUID+312,195069,1,1,1,-980.894,-71.7934,20.7099,-0.157079,0,0,0,1,180,100,1),
(@GUID+313,195069,1,1,1,-980.365,-72.3872,20.7085,-0.890117,0,0,0,1,180,100,1);
-- Assignment of gameobjects to event
DELETE FROM `game_event_gameobject` WHERE `eventEntry`=51 AND `guid` BETWEEN @GUID AND @GUID+314;
INSERT INTO `game_event_gameobject` (`eventEntry`, `guid`) VALUES
(51,@GUID),(51,@GUID+1),(51,@GUID+2),(51,@GUID+3),(51,@GUID+4),(51,@GUID+5),(51,@GUID+6),(51,@GUID+7),(51,@GUID+8),(51,@GUID+9),(51,@GUID+10),
(51,@GUID+11),(51,@GUID+12),(51,@GUID+13),(51,@GUID+14),(51,@GUID+15),(51,@GUID+16),(51,@GUID+17),(51,@GUID+18),(51,@GUID+19),(51,@GUID+20),
(51,@GUID+21),(51,@GUID+22),(51,@GUID+23),(51,@GUID+24),(51,@GUID+25),(51,@GUID+26),(51,@GUID+27),(51,@GUID+28),(51,@GUID+29),(51,@GUID+30),
(51,@GUID+31),(51,@GUID+32),(51,@GUID+33),(51,@GUID+34),(51,@GUID+35),(51,@GUID+36),(51,@GUID+37),(51,@GUID+38),(51,@GUID+39),(51,@GUID+40),
(51,@GUID+41),(51,@GUID+42),(51,@GUID+43),(51,@GUID+44),(51,@GUID+45),(51,@GUID+46),(51,@GUID+47),(51,@GUID+48),(51,@GUID+49),(51,@GUID+50),
(51,@GUID+51),(51,@GUID+52),(51,@GUID+53),(51,@GUID+54),(51,@GUID+55),(51,@GUID+56),(51,@GUID+57),(51,@GUID+58),(51,@GUID+59),(51,@GUID+60),
(51,@GUID+61),(51,@GUID+62),(51,@GUID+63),(51,@GUID+64),(51,@GUID+65),(51,@GUID+66),(51,@GUID+67),(51,@GUID+68),(51,@GUID+69),(51,@GUID+70),
(51,@GUID+71),(51,@GUID+72),(51,@GUID+73),(51,@GUID+74),(51,@GUID+75),(51,@GUID+76),(51,@GUID+77),(51,@GUID+78),(51,@GUID+79),(51,@GUID+80),
(51,@GUID+81),(51,@GUID+82),(51,@GUID+83),(51,@GUID+84),(51,@GUID+85),(51,@GUID+86),(51,@GUID+87),(51,@GUID+88),(51,@GUID+89),(51,@GUID+90),
(51,@GUID+91),(51,@GUID+92),(51,@GUID+93),(51,@GUID+94),(51,@GUID+95),(51,@GUID+96),(51,@GUID+97),(51,@GUID+98),(51,@GUID+99),(51,@GUID+100),
(51,@GUID+101),(51,@GUID+102),(51,@GUID+103),(51,@GUID+104),(51,@GUID+105),(51,@GUID+106),(51,@GUID+107),(51,@GUID+108),(51,@GUID+109),(51,@GUID+110),
(51,@GUID+111),(51,@GUID+112),(51,@GUID+113),(51,@GUID+114),(51,@GUID+115),(51,@GUID+116),(51,@GUID+117),(51,@GUID+118),(51,@GUID+119),(51,@GUID+120),
(51,@GUID+121),(51,@GUID+122),(51,@GUID+123),(51,@GUID+124),(51,@GUID+125),(51,@GUID+126),(51,@GUID+127),(51,@GUID+128),(51,@GUID+129),(51,@GUID+130),
(51,@GUID+131),(51,@GUID+132),(51,@GUID+133),(51,@GUID+134),(51,@GUID+135),(51,@GUID+136),(51,@GUID+137),(51,@GUID+138),(51,@GUID+139),(51,@GUID+140),
(51,@GUID+141),(51,@GUID+142),(51,@GUID+143),(51,@GUID+144),(51,@GUID+145),(51,@GUID+146),(51,@GUID+147),(51,@GUID+148),(51,@GUID+149),(51,@GUID+150),
(51,@GUID+151),(51,@GUID+152),(51,@GUID+153),(51,@GUID+154),(51,@GUID+155),(51,@GUID+156),(51,@GUID+157),(51,@GUID+158),(51,@GUID+159),(51,@GUID+160),
(51,@GUID+161),(51,@GUID+162),(51,@GUID+163),(51,@GUID+164),(51,@GUID+165),(51,@GUID+166),(51,@GUID+167),(51,@GUID+168),(51,@GUID+169),(51,@GUID+170),
(51,@GUID+171),(51,@GUID+172),(51,@GUID+173),(51,@GUID+174),(51,@GUID+175),(51,@GUID+176),(51,@GUID+177),(51,@GUID+178),(51,@GUID+179),(51,@GUID+180),
(51,@GUID+181),(51,@GUID+182),(51,@GUID+183),(51,@GUID+184),(51,@GUID+185),(51,@GUID+186),(51,@GUID+187),(51,@GUID+188),(51,@GUID+189),(51,@GUID+190),
(51,@GUID+191),(51,@GUID+192),(51,@GUID+193),(51,@GUID+194),(51,@GUID+195),(51,@GUID+196),(51,@GUID+197),(51,@GUID+198),(51,@GUID+199),(51,@GUID+200),
(51,@GUID+201),(51,@GUID+202),(51,@GUID+203),(51,@GUID+204),(51,@GUID+205),(51,@GUID+206),(51,@GUID+207),(51,@GUID+208),(51,@GUID+209),(51,@GUID+210),
(51,@GUID+211),(51,@GUID+212),(51,@GUID+213),(51,@GUID+214),(51,@GUID+215),(51,@GUID+216),(51,@GUID+217),(51,@GUID+218),(51,@GUID+219),(51,@GUID+220),
(51,@GUID+221),(51,@GUID+222),(51,@GUID+223),(51,@GUID+224),(51,@GUID+225),(51,@GUID+226),(51,@GUID+227),(51,@GUID+228),(51,@GUID+229),(51,@GUID+230),
(51,@GUID+231),(51,@GUID+232),(51,@GUID+233),(51,@GUID+234),(51,@GUID+235),(51,@GUID+236),(51,@GUID+237),(51,@GUID+238),(51,@GUID+239),(51,@GUID+240),
(51,@GUID+241),(51,@GUID+242),(51,@GUID+243),(51,@GUID+244),(51,@GUID+245),(51,@GUID+246),(51,@GUID+247),(51,@GUID+248),(51,@GUID+249),(51,@GUID+250),
(51,@GUID+251),(51,@GUID+252),(51,@GUID+253),(51,@GUID+254),(51,@GUID+255),(51,@GUID+256),(51,@GUID+257),(51,@GUID+258),(51,@GUID+259),(51,@GUID+260),
(51,@GUID+261),(51,@GUID+262),(51,@GUID+263),(51,@GUID+264),(51,@GUID+265),(51,@GUID+266),(51,@GUID+267),(51,@GUID+268),(51,@GUID+269),(51,@GUID+270),
(51,@GUID+271),(51,@GUID+272),(51,@GUID+273),(51,@GUID+274),(51,@GUID+275),(51,@GUID+276),(51,@GUID+277),(51,@GUID+278),(51,@GUID+279),(51,@GUID+280),
(51,@GUID+281),(51,@GUID+282),(51,@GUID+283),(51,@GUID+284),(51,@GUID+285),(51,@GUID+286),(51,@GUID+287),(51,@GUID+288),(51,@GUID+289),(51,@GUID+290),
(51,@GUID+291),(51,@GUID+292),(51,@GUID+293),(51,@GUID+294),(51,@GUID+295),(51,@GUID+296),(51,@GUID+297),(51,@GUID+298),(51,@GUID+299),(51,@GUID+300),
(51,@GUID+301),(51,@GUID+302),(51,@GUID+303),(51,@GUID+304),(51,@GUID+305),(51,@GUID+306),(51,@GUID+307),(51,@GUID+308),(51,@GUID+309),(51,@GUID+310),
(51,@GUID+311),(51,@GUID+312),(51,@GUID+313);
-- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Issue 4803: To Catch a Sparrowhawk
-- Sparrowhawk SAI
SET @Sparrowhawk := 22979;
SET @Net :=         39810;
SET @ItemSpell :=   39812;
SET @QuestItem :=   32320;
SET @Script :=      39810;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@Sparrowhawk;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@Sparrowhawk AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@Sparrowhawk,0,0,0,13,0,100,0,0,0,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Sparrowhawk - On target casting  spell on it - Flee'),
(@Sparrowhawk,0,1,2,8,0,100,0,@Net,0,0,0,85,@ItemSpell,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Sparrowhawk - On spell hit by net - Ivoker cast on self spell for item'),
(@Sparrowhawk,0,2,3,61,0,100,0,0,0,0,0,47,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Sparrowhawk - Linked with previous event - Set unseen'),
(@Sparrowhawk,0,3,0,61,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Sparrowhawk - Linked with previous event - Despawn in 1 sec');
-- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Issue 4843: Stop the Ascension!
-- Halfdan SAI
SET @Halfdan := 23671;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@Halfdan;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@Halfdan AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@Halfdan,0,0,0,54,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,2000,0,0,0,0,0, 'Halfdan - On summoned - Say line 1'),
(@Halfdan,0,1,0,52,0,100,0,0,@Halfdan,0,0,1,1,2000,0,0,0,0,1,0,0,0,0,0,0,0, 'Halfdan - On text 1 over - Say line 2'),
(@Halfdan,0,2,3,52,0,100,0,1,@Halfdan,0,0,2,14,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Halfdan - IC - Change faction to unfriendly'),
(@Halfdan,0,3,0,61,0,100,0,0,0,0,0,46,1,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Halfdan - Linked with previous event - Move 1 forward to aggro'),
(@Halfdan,0,4,0,0,0,100,0,2000,5000,9500,11500,11,35263,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Halfdan - IC - Cast Frost attack'),
(@Halfdan,0,5,0,0,0,100,0,2500,5000,6000,10000,11,32736,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Halfdan - IC - Cast Mortal Strike'),
(@Halfdan,0,6,0,0,0,100,0,1250,5000,5000,6000,11,12169,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Halfdan - IC - Cast Shield Block'),
(@Halfdan,0,7,0,0,0,100,0,3000,8000,4000,12000,11,32015,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Halfdan - IC - Cast Knockdown'),
(@Halfdan,0,8,0,9,0,100,0,8,25,5000,5000,11,19131,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Halfdan - On target in range - Cast Shield Charge'),
(@Halfdan,0,9,10,2,0,100,1,75,75,120000,120000,1,2,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Halfdan - At 75% HP - Say line 3'),
(@Halfdan,0,10,0,61,0,100,0,0,0,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Halfdan - Linked with previous event - Cast Enrage on self'),
(@Halfdan,0,11,0,2,0,100,1,25,25,120000,120000,1,3,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Halfdan - At 25% HP - Say line 4'),
(@Halfdan,0,12,13,1,0,100,0,20000,20000,20000,20000,47,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Halfdan - OOC more than 20 sec - Set unseen'),
(@Halfdan,0,13,0,61,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Halfdan - Linked with previous event - Despawn in 1 sec');
-- Texts
DELETE FROM `creature_text` WHERE `entry`=@Halfdan;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@Halfdan,0,0, 'You think I do not know what you are trying to do? You think I haven''t been watching you?',12,0,100,1,2000,0, 'Halfdan'),
(@Halfdan,1,0, 'Hah! You thought to interfere with my ascension? Nothing can stop me now!',12,0,100,1,2000,0, 'Halfdan'),
(@Halfdan,2,0, 'You will not stop my ascension, tiny $C. Time to die!',14,0,100,1,2000,0, 'Halfdan'),
(@Halfdan,3,0, 'No! You will not defeat me!',14,0,100,1,1000,0, 'Halfdan');
-- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Issue 4996: Melding of Influences
-- Primal Ooze and Captured Fel Ooze SAIs
SET @POoze         :=  6557;
SET @CFOoze        := 10290;
SET @GFOoze        :=  9621; -- Gargantuan Ooze = result of merging
SET @SpellTrigger  := 16031; -- Cast Releasing Corrupt Ooze - can be used only with target of Primal Ooze to summon the Corrupted Ooze and trigger events
SET @MergingOozes  := 16032; -- Spell visual for Oozes at the moment of meging
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry` IN (@POoze,@CFOoze);
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid` IN (@POoze,@CFOoze);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@POoze,0,0,0,8,0,100,0,@SpellTrigger,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Primal Ooze - On hit by spell Releasing Ooze - Set phase 2'),
-- Phase 2 - used to delay a bit Primal Ooze actions, so the Corrupted Ooze will be spawned
(@POoze,0,1,2,60,2,100,1,1500,1500,0,0,45,0,1,0,0,0,0,9,@CFOoze,0,35,0,0,0,0, 'Primal Ooze - On event update in phase 2 - Set data 0 1 on Corrupted Ooze'),
(@POoze,0,2,0,61,2,100,0,0,0,0,0,29,0,0,10290,1,1,0,9,@CFOoze,0,35,0,0,0,0, 'Primal Ooze - Linked with previous event - Follow Captured felwood ooze'),
(@POoze,0,3,4,65,2,100,0,0,0,0,0,47,0,0,0,0,0,0,0,0,1,0,0,0,0,0, 'Primal Ooze - On follow complete - Set unseen'),
(@POoze,0,4,5,61,2,100,0,0,0,0,0,12,@GFOoze,6,20000,0,0,0,1,0,0,0,0,0,0,0, 'Primal Ooze - Linked with previous event - Spawn Gargantuan Ooze'),
(@POoze,0,5,6,61,2,100,0,0,0,0,0,11,@MergingOozes,0,0,0,0,0,9,@GFOoze,0,5,0,0,0,0, 'Captured Fel Ooze - Linked with previous event - Cast Merging Oozes on Gargantuan Ooze'),
(@POoze,0,6,0,61,2,100,0,0,0,0,0,41,50,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Primal Ooze - Linked with previous event - Despawn self'),
-- <<<>>>>
(@CFOoze,0,0,0,38,0,100,0,0,1,0,0,29,0,0,@POoze,0,1,0,9,@POoze,0,20,0,0,0,0, 'Captured Fel Ooze - On data set 0 1 - Follow Primal Ooze in less than 20 range'),
(@CFOoze,0,1,2,65,0,100,0,0,0,0,0,47,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Captured Fel Ooze - On follow complete - Set unseen'),
(@CFOoze,0,2,0,61,0,100,0,0,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Captured Fel Ooze - Linked with previous event - Despawn');
-- Add conditions for Releasing Corrupt Ooze
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=17 AND `SourceEntry`=@SpellTrigger;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition` ,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(17,0,@SpellTrigger,0,0,31,1,3,@POoze,0,0,0, '', 'Releasing Corrupted Ooze can be casted only on Primal Ooze');
-- Condition for Merging Oozes so it can hit only Gargantuan Ooze
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=@MergingOozes;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition` ,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(13,1,@MergingOozes,0,0,31,0,3,@GFOoze,0,0,0, '', 'Merging Oozes can hit only Gargantuan Ooze');
-- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DELETE FROM `creature_addon` WHERE `guid`=53882;
