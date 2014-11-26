// Author:	Jason Downing
//   Date:	11/16/2014

typedef enum{MODE_A, MODE_B, MODE_C, MODE_D, MODE_E} mode_t;

//           %ebp+8  %ebp+12      %ebp+16
int switch3(int *p1, int *p2, mode_t action)
{
	int result = 0; // edx
    int tmp;        // eax
    int tmp2;       // ecx

    switch(action)
    {
        case MODE_E:
            result = 17;
            goto default:
        
        case MODE_A:
        // LONG PART

        // ebp+8 (p1) goes into eax (tmp), then that goes into edx (result).
            tmp = &p1;
            result = *tmp;   
        // ebp + 12 (p2) goes into ecx (tmp2), that goes into eax (tmp).
            tmp2 = &p2;
            tmp = *tmp2;     // which is p1 = *p2;
            tmp2 = tmp;     // which is p2 = p1 
            *tmp2 = tmp;     // which is *p2 = p1

            // Simplified version:
            result = *p1;
            p1 = *p2;
            p2 = p1;
            *p2 = p1;
            goto default:

        case MODE_B:
            // Long version
            result = *p2;
            tmp = *result;
            result = tmp;
            tmp2 = *p1
            result += *tmp2     // this is basically result = *p1 + *p2
            tmp = *p2;
            *tmp = result;      // *p2 = result

            // Short version, if were to simplify.
            result = *p1 + *p2;
            *p2 = result;
            goto default:

        case MODE_C:
            // Long version
            result = p2;
            *result = 15;   // *p2 = 15
            tmp = p1;
            result = *tmp;  // result = *p1

            // Short version
            *p2 = 15;
            result = *p1;
            goto default:

        case MODE_D:
            // Long version
            result = p1;        // tmp = p1
            tmp = *result;
            tmp2 = p2;          // tmp2 = p2
            *tmp2 = tmp;        // *p2 = p1
            result = 17;

            // Short version
            *p2 = p1;
            result = 17;

            // Falls through, not break/

        default:
            // Sets the return value.
            tmp = result;
            break;
    }

	return result;
}