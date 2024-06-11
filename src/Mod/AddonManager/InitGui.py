# -*- coding: utf-8 -*-
# AddonManager gui init module
# (c) 2001 Juergen Riegel
# License LGPL

import AddonManager

LabRPSGui.addLanguagePath(":/translations")
LabRPSGui.addCommand("Std_AddonMgr", AddonManager.CommandAddonManager())

import LabRPS

LabRPS.__unit_test__ += ["TestAddonManagerGui"]
