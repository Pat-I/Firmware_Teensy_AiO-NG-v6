#ifndef MGHANDLERS_H_
#define MGHANDLERS_H_
#include "Arduino.h"
#include "common.h"

void fw_set_settings(struct settings *data)
{
    netConfig.currentIP[0] = data->bd_ip1;
    netConfig.currentIP[1] = data->bd_ip2;
    netConfig.currentIP[2] = data->bd_ip3;
    netConfig.currentIP[3] = data->bd_ip4;
    gpsConfig.gpsPass = data->gps_pass;
    strcpy(gpsConfig.gpsSync, data->gps_sync);
    strcpy(inoVersion, data->fversion);
    save_current_net();
    save_gps();

    MG_DEBUG(("set_settings: %s,%d,%d,%d,%d,%s,%d", data->fversion, data->bd_ip1, data->bd_ip2, data->bd_ip3, data->bd_ip4, data->gps_sync, data->gps_pass));
    MG_DEBUG(("fw_settings: %s,%d,%d,%d,%d,%s,%d", inoVersion, netConfig.currentIP[0], netConfig.currentIP[1], netConfig.currentIP[2], netConfig.currentIP[3], gpsConfig.gpsSync, gpsConfig.gpsPass));
}

void fw_get_settings(struct settings *data)
{
    load_current_net();
    load_gps();
    MG_DEBUG(("fw_settings: %s,%d,%d,%d,%d,%s,%d", inoVersion, netConfig.currentIP[0], netConfig.currentIP[1], netConfig.currentIP[2], netConfig.currentIP[3], gpsConfig.gpsSync, gpsConfig.gpsPass));
    data->bd_ip1 = netConfig.currentIP[0];
    data->bd_ip2 = netConfig.currentIP[1];
    data->bd_ip3 = netConfig.currentIP[2];
    data->bd_ip4 = netConfig.currentIP[3];
    data->gps_pass = gpsConfig.gpsPass;
    strcpy(data->gps_sync, gpsConfig.gpsSync);
    strcpy(data->fversion, inoVersion);
    MG_DEBUG(("get_settings: %s,%d,%d,%d,%d,%s,%d", data->fversion, data->bd_ip1, data->bd_ip2, data->bd_ip3, data->bd_ip4, data->gps_sync, data->gps_pass));
}

void fw_set_ins_cfg(struct ins_cfg *data)
{
    MG_DEBUG(("Set INS Cfg"));
    SerialGPS1.println(data->insMode);
    // insCfg.eprm = data->insEprm;
    // strcpy(insCfg.enable, data->insEn);
    // insCfg.timeOut = data->insTOut;
    // insCfg.alVel = data->insAlVel;
    // strcpy(insCfg.vehDir, data->insVehDir);
    // insCfg.whlBase = data->insWhlbase;

    // insCfg.instAglX = data->insInstAngX;
    // insCfg.instAglY = data->insInstAngY;
    // insCfg.instAglZ = data->insInstAngZ;

    // insCfg.levArmX = data->insLevX;
    // insCfg.levArmY = data->insLevY;
    // insCfg.levArmZ = data->insLevZ;
    // insCfg.levArmA = data->insLevA;
    // insCfg.levArmB = data->insLevB;
    // insCfg.levArmC = data->insLevC;

    // insCfg.posOffX = data->insPosOffX;
    // insCfg.posOffY = data->insPosOffY;
    // insCfg.posOffZ = data->insPosOffZ;

    // MG_DEBUG(("set_ins_cfg: %d,%s,%d,%f,%s,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", data->insEprm, data->insEn, data->insTOut, data->insAlVel, data->insVehDir, data->insWhlbase,
    //           data->insInstAngX, data->insInstAngY, data->insInstAngZ, data->insLevX, data->insLevY, data->insLevZ, data->insLevA, data->insLevB, data->insLevC,
    //           data->insPosOffX, data->insPosOffY, data->insPosOffZ));

    // MG_DEBUG(("fw_insCfg: %d,%s,%d,%f,%s,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", insCfg.eprm, insCfg.enable, insCfg.timeOut, insCfg.alVel, insCfg.vehDir, insCfg.whlBase,
    //           insCfg.instAglX, insCfg.instAglY, insCfg.instAglZ, insCfg.levArmX, insCfg.levArmY, insCfg.levArmZ, insCfg.levArmA, insCfg.levArmB, insCfg.levArmC,
    //           insCfg.posOffX, insCfg.posOffY, insCfg.posOffZ));
    
}

void fw_get_ins_cfg(struct ins_cfg *data)
{
    MG_DEBUG(("Get INS Cfg"));
    SerialGPS1.println("MODE");
    strcpy(data->insMode, insCfg.mode);
    // MG_DEBUG(("fw_insCfg: %d,%s,%d,%f,%s,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", insCfg.eprm, insCfg.enable, insCfg.timeOut, insCfg.alVel, insCfg.vehDir, insCfg.whlBase,
    //           insCfg.instAglX, insCfg.instAglY, insCfg.instAglZ, insCfg.levArmX, insCfg.levArmY, insCfg.levArmZ, insCfg.levArmA, insCfg.levArmB, insCfg.levArmC,
    //           insCfg.posOffX, insCfg.posOffY, insCfg.posOffZ));

    
    // data->insEprm = insCfg.eprm;
    // strcpy(data->insEn, insCfg.enable);
    // data->insTOut = insCfg.timeOut;
    // data->insAlVel = insCfg.alVel;
    // strcpy(data->insVehDir, insCfg.vehDir);
    // data->insWhlbase = insCfg.whlBase;

    // data->insInstAngX = insCfg.instAglX;
    // data->insInstAngY = insCfg.instAglY;
    // data->insInstAngZ = insCfg.instAglZ;

    // data->insLevX = insCfg.levArmX;
    // data->insLevY = insCfg.levArmY;
    // data->insLevZ = insCfg.levArmZ;
    // data->insLevA = insCfg.levArmA;
    // data->insLevB = insCfg.levArmB;
    // data->insLevC = insCfg.levArmC;

    // data->insPosOffX = insCfg.posOffX;
    // data->insPosOffY = insCfg.posOffY;
    // data->insPosOffZ = insCfg.posOffZ;

    // MG_DEBUG(("get_ins_cfg: %d,%s,%d,%f,%s,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", data->insEprm, data->insEn, data->insTOut, data->insAlVel, data->insVehDir, data->insWhlbase,
    //           data->insInstAngX, data->insInstAngY, data->insInstAngZ, data->insLevX, data->insLevY, data->insLevZ, data->insLevA, data->insLevB, data->insLevC,
    //           data->insPosOffX, data->insPosOffY, data->insPosOffZ));
}

void fw_set_kwas_cfg(struct kwas_cfg *data)
{
    kwasCfg.useKalmanForSensor = data->kwasEn;
    kwasCfg.intervalINS = data->kwasInt;
    kwasCfg.minSpeedKalman = data->kwasMinSpd;
    kwasCfg.secondsVarianceBuffer = data->kwasVarBufSec;
    kwasCfg.kalmanR = data->kwasKalR;
    kwasCfg.kalmanQ = data->kwasKalQ;
    kwasCfg.whlBase = data->kwasWhlBs;
    MG_DEBUG(("set_kwas_cfg: %d,%f,%f,%d,%f,%f,%f", data->kwasEn, data->kwasInt, data->kwasMinSpd, data->kwasVarBufSec, data->kwasKalR, data->kwasKalQ, data->kwasWhlBs));
    MG_DEBUG(("fw_kwasCfg: %d,%f,%f,%d,%f,%f,%f", kwasCfg.useKalmanForSensor, kwasCfg.intervalINS, kwasCfg.minSpeedKalman, kwasCfg.secondsVarianceBuffer, kwasCfg.kalmanR, kwasCfg.kalmanQ, kwasCfg.whlBase));
    save_kwas();
}

void fw_get_kwas_cfg(struct kwas_cfg *data)
{
    load_kwas();
    MG_DEBUG(("fw_kwasCfg: %d,%f,%f,%d,%f,%f,%f", kwasCfg.useKalmanForSensor, kwasCfg.intervalINS, kwasCfg.minSpeedKalman, kwasCfg.secondsVarianceBuffer, kwasCfg.kalmanR, kwasCfg.kalmanQ, kwasCfg.whlBase));
    data->kwasEn = kwasCfg.useKalmanForSensor;
    data->kwasInt = kwasCfg.intervalINS;
    data->kwasMinSpd = kwasCfg.minSpeedKalman;
    data->kwasVarBufSec = kwasCfg.secondsVarianceBuffer;
    data->kwasKalR = kwasCfg.kalmanR;
    data->kwasKalQ = kwasCfg.kalmanQ;
    data->kwasWhlBs = kwasCfg.whlBase;
    MG_DEBUG(("get_kwas_cfg: %d,%f,%f,%d,%f,%f,%f", data->kwasEn, data->kwasInt, data->kwasMinSpd, data->kwasVarBufSec, data->kwasKalR, data->kwasKalQ, data->kwasWhlBs));
}

void teensyReboot(void *param)
{
    SCB_AIRCR = 0x05FA0004;
    (void)param;
}

bool teensyCheckReboot(void)
{
    return false;
}

void teensyStartReboot(void)
{
    mg_timer_add(&g_mgr, 500, 0, teensyReboot, NULL);
}

#endif // MGHANDLERS_H_