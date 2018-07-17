#define _NWINGS     5
#define _REFSG_PN   10
#define _NSMPLS     4096
#define _F_SH       10

int nms_smpl;
int arvls[_NSMPLS];
unsigned int rfidx[_NSMPLS];

void setup() {
  // Set the pin modes.
  pinMode(_REFSG_PN, INPUT);
  nms_smpl = int(1000.0 / _F_SH)
}


void loop() 
{
    // Start calling the ref_sgnl function to count blades.
    ref_sgnl();

    if (/* read start measurement command from control */) {
        measurement();
    }
    
}

void measurement() {
    unsigned long nms = 0;
    bool rfsgnl = false;
    unsigned int nidx = 0;
    int res = 0;

    while (nidx < _NSMPLS) {
        // Check if ref signal has been set. Do not reset signal.
        if (rfsgnl == false) {
            rfsgnl = ref_sgnl();
        }
    
        // Check if a new accel value has to be stored.
        if (millis() % nms_smpl < nms) {
            nms = 0;
            rfsgnl = process_ref_signal(nidx, rfsgnl);
            res = rd_accl(arvls[nidx++]);
        }

        /*
        SEND DATA
        */
    }
}


inline bool process_ref_signal(unsigned int nidx, bool refsgnl)
{
    static unsigned int n_sidx = 0;
    if (refsgnl == true) {
        rfidx[n_sidx] = nidx;
    }
    return false;
}


bool ref_sgnl(void)
{
    // Only every nth wing is counted to create the reference signal.
    static int wng_ct = 0;
    static int lst_st = 0;
    int inpt_st = 0;
    bool res = false

    // If input stat has not changed exit function.
    inpt_st = digitalReal(_REFSG_PN);
    if (inpt_st == lst_st) {
        return false;
    }
    
    // High-Low Flank triggers the sensor.
    lst_st = inpt_st;
    if (inpt_st == 0) {
        wng_ct++;
        if (wng_ct % N_WINGS == 0) {
            wng_ct = 0
            res = true;
        }
    }
    
    return res;
}


