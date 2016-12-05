/*//////////////////////////////////////////////////////////////////////////////
 
This code serchaes through the reactions and when duplicates are found keeps only
 the one with a specific flag. The code was written to keep reactions with flag "talys".
 To modify it replace the tag with whatever is needed in lines 127 and 149.

//////////////////////////////////////////////////////////////////////////////*/


#include <Libnucnet__Reac.h>

int remove_talys_duplicate( Libnucnet__Reaction *, Libnucnet__Reac * );

int main( int argc, char * argv[] ) {

  Libnucnet__Reac *p_my_reactions, *p_my_duplicates;

  /*============================================================================
  // Check input.
  //==========================================================================*/

   if ( argc < 3 || argc > 4 ) {
      fprintf(
        stderr, "\nUsage: %s filename output_file xpath\n\n", argv[0]
      );
      fprintf(
        stderr, "  filename = input reaction xml file\n\n"
      );
      fprintf(
        stderr, "  output_file = output reaction xml file\n\n"
      );
      fprintf(
        stderr, "  xpath = reaction xpath expression (optional)\n\n"
      );

      return EXIT_FAILURE;
   }

  /*============================================================================
  // Read reactions.
  //==========================================================================*/

  if( argv[3] )
    p_my_reactions = Libnucnet__Reac__new_from_xml( argv[1], argv[3] );
  else
    p_my_reactions = Libnucnet__Reac__new_from_xml( argv[1], NULL );

  /*============================================================================
  // Print number of reactions.
  //==========================================================================*/

  fprintf(
    stdout,
    "\nThere are %lu reactions.\n\n",
    (unsigned long) Libnucnet__Reac__getNumberOfReactions( p_my_reactions )
  );

  /*============================================================================
  // Find duplicates.
  //==========================================================================*/

  p_my_duplicates = Libnucnet__Reac__getDuplicateReactions( p_my_reactions );

  /*============================================================================
  // Print number of duplicates.
  //==========================================================================*/

  fprintf(
    stdout,
    "There are %lu duplicates.\n\n",
    (unsigned long) Libnucnet__Reac__getNumberOfReactions( p_my_duplicates )
  );

  /*============================================================================
  // Remove duplicates.
  //==========================================================================*/

  Libnucnet__Reac__iterateReactions(
    p_my_duplicates,
    (Libnucnet__Reaction__iterateFunction) remove_talys_duplicate,
    p_my_reactions
  );

  /*============================================================================
  // Print number of reactions.
  //==========================================================================*/

  fprintf(
    stdout,
    "\nThere are now %lu reactions.\n\n",
    (unsigned long) Libnucnet__Reac__getNumberOfReactions( p_my_reactions )
  );

  /*============================================================================
  // Output the cleaned up structure.
  //==========================================================================*/

  Libnucnet__Reac__writeToXmlFile( p_my_reactions, argv[2] );

  /*============================================================================
  // Clean up.
  //==========================================================================*/

  Libnucnet__Reac__free( p_my_duplicates );
  Libnucnet__Reac__free( p_my_reactions );

  return EXIT_SUCCESS;

}

/*##############################################################################
// remove_talys_duplicate().
//############################################################################*/

int
remove_talys_duplicate(
  Libnucnet__Reaction *p_reaction, Libnucnet__Reac *p_reac
)
{

     printf( "%s\n", Libnucnet__Reaction__getString( p_reaction ) );

  if(
    strcmp(
      Libnucnet__Reaction__getSource( p_reaction ),
      "rapp"
    ) != 0
  )
  {
    fprintf(
      stdout,
      "Removing %s (Data source: %s)\n",
      Libnucnet__Reaction__getString( p_reaction ),
      Libnucnet__Reaction__getSource( p_reaction )
    );
    Libnucnet__Reac__removeReaction(
      p_reac,
      Libnucnet__Reac__getReactionByString(
        p_reac, Libnucnet__Reaction__getString( p_reaction )
      )
    );
  }
  else if(
    strcmp(
      Libnucnet__Reaction__getSource(
        Libnucnet__Reaction__getParentDuplicate( p_reaction )
      ),
      "rapp"
    ) != 0
  )
  {
    fprintf(
      stdout,
      "Removing %s (Data source: %s)\n",
      Libnucnet__Reaction__getString(
        Libnucnet__Reaction__getParentDuplicate( p_reaction )
      ),
      Libnucnet__Reaction__getSource(
        Libnucnet__Reaction__getParentDuplicate( p_reaction )
      )
    );
    Libnucnet__Reac__removeReaction(
      p_reac,
      Libnucnet__Reaction__getParentDuplicate( p_reaction )
    );
  }

  return 1;

}
