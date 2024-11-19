import java.io.File;

/**
 * @date: 11/2024
 * @author: Thiago Pereira de Oliveira
 * @details: Meu código fonte dos TPs para Java, onde guardo a base para as futuras atividades
 * do TP 4.
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////
// BIBLIOTECAS

/////////////////////////////////////////////////////////////////////////////////////////////////////
// CORE

// classe de armazenamento / funções interessantes de se ter como um todo. Um QOL no geral.
class Core
{
    public static boolean verde = false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// POKEMON

// classe pokemon
class Pokemon
{
    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// GERENCIADOR

// classe que gerencia pokemons.
class Gerenciador
{

    // construtor
    public Gerenciador ()
    {
        File arquivo = new File ("pokemon.csv");

        if (!arquivo.exists ())
        {
            arquivo = new File ("/tmp/pokemon.csv");

            if (!arquivo.exists ()) 
            throw new Exception ("Arquivo .CSV não encontrado!");

            Core.verde = true;
        }

        
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN

public class Main
{
    public static void main (String args [])
    {
        
    }
}