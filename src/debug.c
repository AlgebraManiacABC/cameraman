#include "debug.h"

const char * errorMessages[] =
{
	"Unknown error!",
	"Couldn't open file!",
	"Shader compilation failure!",
	"Given pointer was NULL!",
	"Not enough memory!"
};

char * errorString = NULL;
errType lastError = ERR_CODE;
Uint32 lastErrorCode = ERR_UNDEF;

void setError(errType type, ...)
{
	va_list args;
	va_start(args, type);

	if(type == ERR_CODE)
	{
		lastErrorCode = va_arg(args,Uint32);
		va_end(args);
		lastError = ERR_CODE;
		return;
	}

	//	setErrorMesg to the formatted string (second arg)
	char * fmt = va_arg(args, char *);
	if(errorString)
	{
		free(errorString);
		errorString = NULL;
	}
	vasprintf(&errorString,fmt,args);
	va_end(args);
	lastError = ERR_MESG;
}

const char * getError(void)
{
	if(lastError == ERR_CODE)
	{
		return errorMessages[lastErrorCode];
	}

	if(!errorString)
	{
		return errorMessages[ERR_UNDEF];
	}

	return errorString;
}

void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  fprintf( stderr, "%s type = 0x%x, severity = 0x%x, message:\n\t%s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}