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