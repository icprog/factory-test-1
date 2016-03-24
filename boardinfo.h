struct config_reg_ {
    unsigned int  reg0;  //0x00~0x03        
    unsigned int  reg1;  //0x04~0x07
    unsigned int  reg2;  //0x08~0x0B
    unsigned int  reg3;  //0x0C~0x0F
};

union board_priv
{
    char reg[16];
    struct config_reg_ config_reg;
};

typedef struct board_info_s
{
    unsigned short  magic;
    unsigned short  pad;     
    unsigned char   macaddrs;
    char    rsvd0;
    unsigned char   macbase[6];
    unsigned char   prod_rev[8];
    
    unsigned short  brd_id; 
    char    rsvd1[2];   
    unsigned char   pcb_rev[8]; 
    unsigned char   bom_rev[8];
    unsigned short  boot_rev;
    unsigned short  cpld_rev;
    unsigned char   rsvd2[4];
    
    union  board_priv brd_priv;	
    char  date_code[16];	 
    char  brd_pn[32]; 
    char  brd_sn[32]; 
    
    char  prod_model[32]; 
    char  prod_pn[32];  
    char  prod_sn[64];  
    char  prod_bn[16];  
    char  rsvd3[16];
    
    char  vendor[32];
    char  oemsn[32];
    char  oempn[32]; 
    char  rsvd4[32];
} board_info_t;

