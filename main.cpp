#include "stdafx.h"
#include "parser.h"
#include "scanner.h"
#include "parsetools.h"
#include "codegen.h"


int main( int argc , char* argv[] )
{
	if ( argc == 1 )
	{
		cout << "Logvinenko, 236 group.\n";
		return 0;
	}

	if ( argc > 1 )//will have to do smth
	{
		Scanner scanner( argv[1] );
		if ( scanner.OK() )
		{
			if ( argc == 2 )//do all that is possible
			{
				try
				{
					TSymTable* parsed_program = new TSymTable();
					parsed_program->Init();
					Parser parser ( scanner , parsed_program , false );
					parser.ParseProgram();
					parsed_program->Output( 0 );
					CodeGen *code_gen = new CodeGen( argv[1] , false , true );
					parsed_program->GenGlobal( code_gen );
				}
				catch( Error e )
				{
					e.ErrorPrint();
				}
				catch( std::exception e )
				{}
			}

			if ( argc >= 3 )//selectively
			{
				string arg2 = argv[2];
				if ( arg2 == "-l" )//only lexer
				{
					do
					{
						try
						{
							scanner.Next();
							scanner.OutToken();
						}
						catch ( Error err )
						{
							err.ErrorPrint();
						}
					}
					while ( scanner.GetToken().GetType() != eof );
					return 0;
				}

				if ( ( arg2 == "-p" ) || ( arg2 == "-g" ) || ( arg2 == "-pg" ) )//parser and gen
				{
					try
					{
						bool optimizing = false,
							commenting = false;
						if ( argc >= 4 )
						{
							string arg3 = argv[3];
							if ( "-o" == arg3 )							
								optimizing = true;
							if ( "-c" == arg3 )
								commenting = true;							
						}
						TSymTable *parsed_program = new TSymTable();
						parsed_program->Init();
						Parser parser( scanner , parsed_program , optimizing );
						parser.ParseProgram();

						if ( arg2 != "-g" )
							parsed_program->Output( 0 );

						if ( arg2 != "-p" )
						{
							CodeGen *code_gen = new CodeGen( argv[1] , optimizing , commenting );
							parsed_program->GenGlobal( code_gen );
						}
					}
					catch( Error e )
					{
						e.ErrorPrint();
					}
					catch( std::exception e )
					{}
					return 0;
				}
			}
		}
		else
			cout << "missing file " << argv[1] << endl;
		return 0;
	}
}