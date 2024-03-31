#include "table14.h"

TABLE14(players, P_POSX, P_POSY, P_HP, P_NAME);

typedef char fixed_string[16];

int main()
{
    TABLE14_INIT_START(players, 100);
    TABLE14_INIT_COL(P_POSX, uint32_t);
    TABLE14_INIT_COL(P_POSY, uint32_t);
    TABLE14_INIT_COL(P_HP, float);
    TABLE14_INIT_COL(P_NAME, fixed_string);
    TABLE14_INIT_END;

    uint32_t *posx = TABLE14_GET(players, P_POSX, uint32_t);

    return EXIT_SUCCESS;
}