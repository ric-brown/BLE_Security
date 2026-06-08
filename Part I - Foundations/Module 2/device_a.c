/*
 * device_a.c --  NimBLE peripheral security configuration excerpt
 *
 * MODULE 2, PART C.  Classify this device's pairing tier
 * (no pairing / Just Works / authenticated) from the Security Manager
 * configuration and the characteristic flags below. Cite the lines that
 * prove your answer.
 */
#include "host/ble_hs.h"
#include "host/ble_gatt.h"
#include "services/gap/ble_svc_gap.h"

static int hr_access(uint16_t conn_handle, uint16_t attr_handle,
                     struct ble_gatt_access_ctxt *ctxt, void *arg);

/* ---- GATT services ---- */
static const struct ble_gatt_svc_def gatt_svcs[] = {
    {
        .type = BLE_GATT_SVC_TYPE_PRIMARY,
        .uuid = BLE_UUID16_DECLARE(0x180D),              /* Heart Rate */
        .characteristics = (struct ble_gatt_chr_def[]){
            {
                .uuid      = BLE_UUID16_DECLARE(0x2A37), /* HR Measurement */
                .access_cb = hr_access,
                .flags     = BLE_GATT_CHR_F_READ
                           | BLE_GATT_CHR_F_READ_ENC
                           | BLE_GATT_CHR_F_NOTIFY,
            },
            { 0 }
        },
    },
    { 0 }
};

/* ---- Security Manager configuration ---- */
void peripheral_security_init(void)
{
    ble_hs_cfg.sm_bonding = 1;
    ble_hs_cfg.sm_mitm    = 0;
    ble_hs_cfg.sm_sc      = 1;
    ble_hs_cfg.sm_io_cap  = BLE_HS_IO_NO_INPUT_OUTPUT;
}

/* ---- GAP event handler ---- */
static int gap_event(struct ble_gap_event *event, void *arg)
{
    switch (event->type) {
    case BLE_GAP_EVENT_CONNECT:     return 0;
    case BLE_GAP_EVENT_DISCONNECT:  return 0;
    case BLE_GAP_EVENT_ENC_CHANGE:  return 0;   
    }
    return 0;
}
