#include "client.h"
#include <readline/readline.h>

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();
	t_log* 		log_create(char* tp0, char* logs, bool is_active_console, t_log_level level);

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"
	log_info(logger, "hola soy un log");


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();
	 

	// Usando el config creado previamente, leemos los valores del config y los har* 
	
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	ip = config_get_string_value(config, "IP");
	puerto= config_get_string_value(config, "PUERTO");
	valor= config_get_string_value(config, "CLAVE");
		// Loggeamos el valor de config
		log_info(logger, "VALOR LEIDO: %s", valor);



	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor,conexion);

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
	printf ("TERMINO EL PROGRAMA");
}

t_log* iniciar_logger(void)
{	
	t_log* nuevo_logger = log_create("tp0.log","logger", 1, LOG_LEVEL_INFO);

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	 t_config* nuevo_config = config_create("cliente.config");
	if (nuevo_config==NULL) {
		perror("ERROR");
		exit(EXIT_FAILURE);
	}
	

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");
	log_info(logger, ">> %s", leido);

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	while (strcmp(leido, "") != 0 ){
		free(leido);
		leido = readline("> ");
		log_info(logger, ">> %s", leido);
	
	
		
	}
	
	// ¡No te olvides de liberar las lineas antes de regresar!
free(leido);
}


void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido = NULL;
	t_paquete* paquete = crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete
	 leido = readline("> ");

	 while (strcmp (leido, "")!= 0 ){
		agregar_a_paquete(paquete, leido, strlen(leido) + 1 );
		free(leido);
		leido = readline("> "); }


	 
	free(leido);
	
	enviar_paquete(paquete, conexion);

	eliminar_paquete(paquete);
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	


}


void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}


