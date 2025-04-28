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

void fw_set_ins_config(struct ins_config *data)
{
    strcpy(insConfig.enable, data->insEnable);
    insConfig.timeOut = data->insTimeOut;
    insConfig.alignVelocity = data->insAlignVel;
    strcpy(insConfig.vehicleDir, data->insVehDir);
    insConfig.wheelbase = data->insWheelbase;

    insConfig.installAngleX = data->insInstAngleX;
    insConfig.installAngleY = data->insInstAngleY;
    insConfig.installAngleZ = data->insInstAngleZ;

    insConfig.leverArmX = data->insLeverX;
    insConfig.leverArmY = data->insLeverY;
    insConfig.leverArmZ = data->insLeverZ;
    insConfig.leverArmA = data->insLeverA;
    insConfig.leverArmB = data->insLeverB;
    insConfig.leverArmC = data->insLeverC;

    insConfig.posOffsetX = data->insPosOffsetX;
    insConfig.posOffsetY = data->insPosOffsetY;
    insConfig.posOffsetZ = data->insPosOffsetZ;

    insConfig.initAttitudePitch = data->insInitAttPitch;
    insConfig.initAttitudeRoll = data->insInitAttRoll;
    insConfig.initAttitudeAzimuth = data->insInitAttAzimuth;
    insConfig.initAttitudeStdPitch = data->insInitAttStdPitch;
    insConfig.initAttitudeStdRoll = data->insInitAttStdRoll;
    insConfig.initAttitudeStdAzimuth = data->insInitAttStdAzi;

    MG_DEBUG(("set_ins_config: %s,%d,%f,%s,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", data->insEnable, data->insTimeOut, data->insAlignVel, data->insVehDir, data->insWheelbase,
              data->insInstAngleX, data->insInstAngleY, data->insInstAngleZ, data->insLeverX, data->insLeverY, data->insLeverZ, data->insLeverA, data->insLeverB, data->insLeverC,
              data->insPosOffsetX, data->insPosOffsetY, data->insPosOffsetZ, data->insInitAttPitch, data->insInitAttRoll, data->insInitAttAzimuth, data->insInitAttStdPitch, data->insInitAttStdRoll, data->insInitAttStdAzi));

    MG_DEBUG(("fw_insConfig: %s,%d,%f,%s,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", insConfig.enable, insConfig.timeOut, insConfig.alignVelocity, insConfig.vehicleDir, insConfig.wheelbase,
              insConfig.installAngleX, insConfig.installAngleY, insConfig.installAngleZ, insConfig.leverArmX, insConfig.leverArmY, insConfig.leverArmZ, insConfig.leverArmA, insConfig.leverArmB, insConfig.leverArmC,
              insConfig.posOffsetX, insConfig.posOffsetY, insConfig.posOffsetZ, insConfig.initAttitudePitch, insConfig.initAttitudeRoll, insConfig.initAttitudeAzimuth,
              insConfig.initAttitudeStdPitch, insConfig.initAttitudeStdRoll, insConfig.initAttitudeStdAzimuth));

    save_ins();
}

void fw_get_ins_config(struct ins_config *data)
{
    load_ins();
    MG_DEBUG(("fw_insConfig: %s,%d,%f,%s,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", insConfig.enable, insConfig.timeOut, insConfig.alignVelocity, insConfig.vehicleDir, insConfig.wheelbase,
              insConfig.installAngleX, insConfig.installAngleY, insConfig.installAngleZ, insConfig.leverArmX, insConfig.leverArmY, insConfig.leverArmZ, insConfig.leverArmA, insConfig.leverArmB, insConfig.leverArmC,
              insConfig.posOffsetX, insConfig.posOffsetY, insConfig.posOffsetZ, insConfig.initAttitudePitch, insConfig.initAttitudeRoll, insConfig.initAttitudeAzimuth,
              insConfig.initAttitudeStdPitch, insConfig.initAttitudeStdRoll, insConfig.initAttitudeStdAzimuth));

    strcpy(data->insEnable, insConfig.enable);
    data->insTimeOut = insConfig.timeOut;
    data->insAlignVel = insConfig.alignVelocity;
    strcpy(data->insVehDir, insConfig.vehicleDir);
    data->insWheelbase = insConfig.wheelbase;

    data->insInstAngleX = insConfig.installAngleX;
    data->insInstAngleY = insConfig.installAngleY;
    data->insInstAngleZ = insConfig.installAngleZ;

    data->insLeverX = insConfig.leverArmX;
    data->insLeverY = insConfig.leverArmY;
    data->insLeverZ = insConfig.leverArmZ;
    data->insLeverA = insConfig.leverArmA;
    data->insLeverB = insConfig.leverArmB;
    data->insLeverC = insConfig.leverArmC;

    data->insPosOffsetX = insConfig.posOffsetX;
    data->insPosOffsetY = insConfig.posOffsetY;
    data->insPosOffsetZ = insConfig.posOffsetZ;

    data->insInitAttPitch = insConfig.initAttitudePitch;
    data->insInitAttRoll = insConfig.initAttitudeRoll;
    data->insInitAttAzimuth = insConfig.initAttitudeAzimuth;
    data->insInitAttStdPitch = insConfig.initAttitudeStdPitch;
    data->insInitAttStdRoll = insConfig.initAttitudeStdRoll;
    data->insInitAttStdAzi = insConfig.initAttitudeStdAzimuth;

    MG_DEBUG(("get_ins_config: %s,%d,%f,%s,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", data->insEnable, data->insTimeOut, data->insAlignVel, data->insVehDir, data->insWheelbase,
              data->insInstAngleX, data->insInstAngleY, data->insInstAngleZ, data->insLeverX, data->insLeverY, data->insLeverZ, data->insLeverA, data->insLeverB, data->insLeverC,
              data->insPosOffsetX, data->insPosOffsetY, data->insPosOffsetZ, data->insInitAttPitch, data->insInitAttRoll, data->insInitAttAzimuth, data->insInitAttStdPitch, data->insInitAttStdRoll, data->insInitAttStdAzi));
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