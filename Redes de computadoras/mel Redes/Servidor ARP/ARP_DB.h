/*PROTOTIPOS DE FUNCIONES*/
void borraDB(MYSQL*);
void creaDB(MYSQL*);
void verRegistros(MYSQL*);
void addToDB(MYSQL*,char*,char*);
void searchIP(MYSQL*, char*, char*);
void printResultSet(MYSQL*);
/*FIN DE PROTOTIPOS DE FUNCIONES*/

/*IMPLEMENTACION DE FUNCIONES*/
void creaDB(MYSQL *con){
	if (mysql_real_connect(con, "localhost", "root", "luis9419", NULL, 0, NULL, 0) == NULL) {
      	fprintf(stderr, "%s\n", mysql_error(con));
      	mysql_close(con);
  	} 

  	if (mysql_query(con, "DROP DATABASE IF EXISTS ARP"))
  		fprintf(stderr, "%s\n", mysql_error(con));
  
 	if (mysql_query(con, "CREATE DATABASE ARP"))
    	fprintf(stderr, "%s\n", mysql_error(con));

   if (mysql_query(con,"USE ARP"))
  		fprintf(stderr, "%s\n", mysql_error(con));    

  	if (mysql_query(con, "CREATE TABLE ARP_TABLE(Id INT NOT NULL AUTO_INCREMENT,IP VARCHAR(20),MAC VARCHAR(20),PRIMARY KEY(Id))"))  
  		fprintf(stderr, "%s\n", mysql_error(con));
}

void verRegistros(MYSQL *con){
	if (mysql_query(con,"USE ARP"))
  		fprintf(stderr, "%s\n", mysql_error(con)); 

	if(mysql_query(con, "SELECT * FROM ARP_TABLE"))
    	fprintf(stderr, "%s\n", mysql_error(con));
  
 printResultSet(con);
}

void addToDB(MYSQL *con,char *IP,char *MAC){
	char query[80];
	int len = sprintf(query,"INSERT INTO ARP_TABLE VALUES(NULL,\"%s\",\"%s\")",IP,MAC);
	if (mysql_real_query(con, query, len))
    	fprintf(stderr, "%s\n", mysql_error(con));
}

void borraDB(MYSQL *con){
	if (mysql_query(con, "DROP DATABASE IF EXISTS ARP"))
  		fprintf(stderr, "%s\n", mysql_error(con));
  
 	if (mysql_query(con, "CREATE DATABASE ARP"))
    	fprintf(stderr, "%s\n", mysql_error(con));

   if (mysql_query(con,"USE ARP"))
  		fprintf(stderr, "%s\n", mysql_error(con));    

  	if (mysql_query(con, "CREATE TABLE ARP_TABLE(Id INT NOT NULL AUTO_INCREMENT,IP VARCHAR(20),MAC VARCHAR(20),PRIMARY KEY(Id))"))  
  		fprintf(stderr, "%s\n", mysql_error(con));

  	printf("\nDATOS BORRADOS CON EXITO\n");
}

void searchIP(MYSQL *con, char *ipchar, char *macchar){
  char query[60]; 
  int len = sprintf(query,"SELECT MAC FROM ARP_TABLE WHERE IP = '%s'",ipchar);
  if (mysql_real_query(con, query, len))
      fprintf(stderr, "%s\n", mysql_error(con));

  MYSQL_RES *result = mysql_store_result(con);

  if(result == NULL)
    fprintf(stderr, "%s\n", mysql_error(con));  

  int num_fields = mysql_num_fields(result),i;

  MYSQL_ROW row;

  if(mysql_num_rows(result) == 0)
    memcpy(macchar,"NULL",5);

  while((row = mysql_fetch_row(result))){ 
    for(i = 0; i < num_fields; i++)
      strcpy(macchar,row[i] ? row[i] : "NULL"); 
      //memcpy(macchar,row[i] ? row[i] : "NULL",strlen(row[i])); 
  }

  mysql_free_result(result);
}

void printResultSet(MYSQL *con){
   MYSQL_RES *result = mysql_store_result(con);

  if(result == NULL)
    fprintf(stderr, "%s\n", mysql_error(con));  

  int num_fields = mysql_num_fields(result),i;

  MYSQL_ROW row;
  MYSQL_FIELD *field;
    
  printf ("\nNumero de registros encontrados: %lu\n\n",(unsigned long) mysql_num_rows(result));

  while((row = mysql_fetch_row(result))){ 
    for(i = 0; i < num_fields; i++){ 
      if (i == 0){              
        while(field = mysql_fetch_field(result))
          printf("  %s     ", field->name);
        printf("\n");           
      }
      printf("  %s  ", row[i] ? row[i] : "NULL"); 
    } 
  }
  printf("\n");
  mysql_free_result(result);
}
/*FIN DE IMPLEMENTACION DE FUNCIONES*/