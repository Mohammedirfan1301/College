/**
 * Read input from a given file, until being told to stop reading characters,
 * or until EOF.
 *
 * IMPORTANT:
 *   The input replaces, entirely, any data that was already in the MYSTRING
 *   object.
 *
 * @param hString
 *   The MYSTRING handle of the string into which the input data should be
 *   placed, replacing any prior data in this string
 *
 * @param hFile
 *   A FILE* handle from which input should be read
 *
 * @param bIgnoreLeadingWhiteSpace
 *   If true, ignore any leading white space. Leading white space means any
 *   spaces, horizontal or vertical tabs, and newlines that occur before any
 *   non-whitespace character has been encountered. The function pointed to be
 *   fTerminate is not called for leading white space, when this argument is
 *   true, but is called when this argument is false.
 *
 * @param fTerminate
 *   A pointer to a function to be called upon reading each character, to
 *   determine whether the character just read is a "terminator", i.e.,
 *   whether mystring_input should return after storing (or not storing, as
 *   indicated by *pbDiscardChar) this character. This function will be called
 *   as each character is read. It must return TRUE (non-zero) if the
 *   just-read character should terminate input. It should set
 *   *pbDiscardChar, as described below, before returning.
 *
 *   The fTerminate function's signature is:
 *     int (* fTerminate)(char ch, int * pbDiscardChar);
 *
 *   with the following documentation:
 *     @param ch
 *       The character that was just read. fTerminate should determine whether
 *       this character is a terminator.
 *
 *     @param pbDiscardChar
 *       Whether this character should be added to the MYSTRING object. Prior
 *       to returning TRUE (non-zero) or FALSE (zero), fTerminate should set
 *       *pbDiscardChar to one of the following values:
 *
 *         0: Do not discard the character. Add it to the MYSTRING object
 *         1: Discard the character. Do not add it to the MYSTRING object
 *
 *     @return
 *       TRUE if this character should cause termination of input; FALSE
 *       otherwise.
 *
 *   The fTerminate function is not called upon EOF.
 *
 * @return
 *   upon failure:
 *     MYSTRING_STATUS_ERROR (any of the arguments are null)
 *
 *   upon success:
 *     MYSTRING_STATUS_SUCCESS
 *
 * @example 1 (fairly simple)
 *   Let's say that you want to accept all "words", i.e., sequences of
 *   characters separated by white space. The white space character should be
 *   discarded. You could write a simple termination function to accept
 *   characters other than white space, discard white space, and terminate
 *   upon reaching any white space. The function must meet the signature
 *   requirements of fTerminate:
 *
 *   int acceptNonWhite(char ch, int * pbDiscardChar)
 *   {
 *     // If the character is white space...
 *     if (isspace(ch))
 *     {
 *       // ... then we want it to be discarded, ...
 *       *pbDiscardChar = TRUE;
 *
 *       // ... and we want to terminate input to this MYSTRING object
 *       return TRUE;
 *     }
 *
 *     // In any other case (non-white), do not discard the character, ...
 *     *pbDiscardChar = FALSE;
 *
 *     // ... and do not terminate input
 *     return FALSE;
 *   }
 *
 *   // Now we can call mystring_input using that function:
 *   ...
 *   status = mystring_input(hString, stdin, 0, acceptNonWhite);
 *   ...
 *
 * @example 2 (more sophisticated)
 *   Assume that you want to accept all sequences of digits, ignoring any even
 *   digit. Any other character is to terminate input and that chraracter is
 *   to be ignored. In this scenario, if the input were "12345 23476abc" then
 *   you want the MYSTRING object to contain "135", and the next time this
 *   function was called with the same arguments, it would retrieve "37". On
 *   the first call, the space is discarded. ON the second call, the 'a' is
 *   discarded. You might define a function such as acceptOddDigits, that
 *   meets the signature requirements of fTerminate:
 *
 *   int acceptOddDigits(char ch, int * pbDiscardChar)
 *   {
 *     // If the character is a digit, ...
 *     if (isdigit(ch))
 *     {
 *       // First, convert the character containing the digit to its numeric
 *       // value.
 *       ch -= '0';
 *
 *       // Discard the character if it is even; do not discard it otherwise.
 *       *pbDiscardChar = (ch % 2 == 0);
 *
 *       // Do not terminate. We want to keep retrieving input.
 *       return FALSE;
 *     }
 *
 *     // It's not a digit. Throw away the character, ...
 *     *pbDiscardChar = TRUE;
 *
 *     // and terminate input into this MYSTRING object
 *     return TRUE;
 *   }
 *
 *   // Now we can call mystring_input using that function:
 *   ...
 *   status = mystring_input(hString, stdin, 0, acceptOddDigits);
 *   ...
 */
MyString_Status mystring_input(MYSTRING pString,
                               FILE * hFile,
                               int bIgnoreLeadingWhiteSpace,
                               int (* fTerminate)(char ch,
                                                  int * pbDiscardChar))
{
    char            input[2] = { '\0', '\0' };
    int             bTerminate = 0;
    int             bIsWhite;
    int             bDiscardChar;
    int             bSeenNonWhite = 0;

    // Validate input
    if (pString == NULL || hFile == NULL || fTerminate == NULL)
    {
        return MYSTRING_STATUS_ERROR;
    }

    // Flush all existing data from the string
    pString->size = 0;

    // Until we reach a terminator...
    do
    {
        // ... get the next character
        input[0] = fgetc(hFile);

        // Have we reached EOF?
        if (input[0] == EOF)
        {
            return MYSTRING_STATUS_SUCCESS;
        }

        // See if this character is white space
        bIsWhite = isspace(input[0]);

        // If we were asked to ignore leading white space, and we haven't yet
        // seen any non-white characters, and this character is white space...
        if (bIgnoreLeadingWhiteSpace && ! bSeenNonWhite && bIsWhite)
        {
            // ... then ignore it
            continue;
        }

        // Is this a non-white character?
        if (! bIsWhite)
        {
            // Yup. Remember that we've seen one
            bSeenNonWhite = 1;
        }

        // Find out whether to keep or discard this character, and whether to
        // terminate after processing this character.
        bTerminate = (* fTerminate)(input[0], &bDiscardChar);

        // Is this character supposed to be added to the string?
        if (! bDiscardChar)
        {
            // Yup. Concatenate it.
            if (mystring_concatenate_c_string(
                    pString, input) != MYSTRING_STATUS_SUCCESS)
            {
                return MYSTRING_STATUS_ERROR;
            }
        }
    } while (! bTerminate);

    // All done!
    return MYSTRING_STATUS_SUCCESS;
}
