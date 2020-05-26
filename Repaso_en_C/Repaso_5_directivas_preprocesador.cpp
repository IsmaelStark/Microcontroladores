 #directivas del preprocesador
 
 #define, #elif, #else, #endif, #error, #if, #ifdef, #ifndef, #include, #message y #undef.

           
Sintaxis
         
#define 	label 	text
#elif 		condition
#else
#endif
#error 		"message"
#if 		condition
#ifdef 		label
#ifndef 	label
#include 	{"filename" | <filename>}
#message 	"message"
#undef 		label

//Descripci�n del comando
#define 	Definir macro
#include 	incluir un archivo de c�digo fuente
#undef 		Cancelar la macro definida
#ifdef 		devuelve verdadero si la macro ya est� definida
#ifndef 	Devuelve verdadero si la macro no est� definida
#if 		Si la condici�n dada es verdadera, compile el siguiente c�digo
#else 		#if alternativas
#elif 		Si la condici�n #if dada anterior no es verdadera y
			la condici�n actual es verdadera, compile el siguiente c�digo
#endif 		Finalizando un bloque de compilaci�n condicional # if ...... # else
#error 		Cuando encuentre un error est�ndar, env�e un mensaje de error
#pragma 	Use m�todos estandarizados para emitir comandos especiales al compilador

//macros pre definidas
__DATE__ La fecha actual, una constante de caracteres expresada en el formato "MMM DD AAAA".
__TIME__ La hora actual, una constante de caracteres expresada en el formato "HH: MM: SS".
__FILE__ Esto contendr� el nombre del archivo actual, una constante de cadena.
__LINE__ Esto contendr� el n�mero de l�nea actual, una constante decimal.
__STDC__ se define como 1 cuando el compilador compila con el est�ndar ANSI.


#ifndef __unix__ // __unix__ is typically defined when targetting Unix 
#error "Only Unix is supported"
#endif
