<?php
/**
 * Funções utilitárias para conexão e operações com o banco de dados
 */

/**
 * Abre e retorna uma nova conexão com o banco de dados postgres
 * @return Object
 */
function _connect()
{
	try {
		// nome padrão da imagem docker contendo o banco
		$host     = "postgres";
		// variaveis de ambiente criadas no docker-compose.yml
		$db 	  = $_ENV["POSTGRES_DB"];
		$user	  = $_ENV["POSTGRES_USER"];
		$password = $_ENV["POSTGRES_PASSWORD"];
		// porta padrão de utilização do serviço postgres
		$port     = "5432";

		return pg_connect("
			host=$host 
			port=$port 
			dbname=$db 
			user=$user 
			password=$password
		");
	} catch (Exception $e) {
		throw new Exception("Connection to database failed! Error: ".$e->getMessage());
	}
}

/**
 * Busca os dados de uma query no banco
 * @param String query = select a ser executado na base
 * @param Array params = filtros do select ["field" => value]
 * @return Array
 */
function _fetchData(string $query, array $params = []) {
	try {
		$conn = _connect();
		// salvando a query preparada com um id aleatorio
		$statement = "stmtname_".rand(0, 99999);

		// preparando a query como uma primeira camada de segurança, para evitar injeção de dados
		pg_prepare($conn, $statement, $query);
		// executando a query com binds
		$result = pg_execute($conn, $statement, $params);

		// retornando todos dados
		return pg_fetch_all($result);
	} catch (Exception $e) {
		throw new Exception("Query invalid! Error: ".$e->getMessage());
	} finally {
		pg_close($conn);
	}
}

/**
 * Verifica se existe um registro no banco
 * @param String query = select a ser executado na base
 * @param Array params = filtros do select ["field" => value]
 * @return Boolean
 */
function _recordExists(string $query, array $params = []) {
	try {
		$conn = _connect();
		// salvando a query preparada com um id aleatorio
		$statement = "stmtname_".rand(0, 99999);

		// preparando a query como uma primeira camada de segurança, para evitar injeção de dados
		pg_prepare($conn, $statement, $query);
		// executando a query com binds
		$result = pg_execute($conn, $statement, $params);

		// retornando todos dados
		return pg_fetch_row($result);
	} catch (Exception $e) {
		throw new Exception("Query invalid! Error: ".$e->getMessage());
	} finally {
		pg_close($conn);
	}
}

/**
 * Deleta dados no banco
 * @param String table = nome da tabela
 * @param Array params = filtros do delete ["field" => value]
 * @return Boolean
 */
function _deleteData(string $table, array $params) {
	try {
		$conn = _connect();
		return pg_delete($conn, $table, $params);
	} catch (Exception $e) {
		throw new Exception("Delete invalid! Error: ".$e->getMessage());
	} finally {
		pg_close($conn);
	}
}

/**
 * Insere dados no banco
 * @param String table = nome da tabela
 * @param Array params = campos a serem inseridos ["field" => value]
 * @return Boolean
 */
function _insertData(string $table, array $params) {
	try {
		$conn = _connect();
		return pg_insert($conn, $table, $params);
	} catch (Exception $e) {
		throw new Exception("Insert invalid! Error: ".$e->getMessage());
	} finally {
		pg_close($conn);
	}
}

/**
 * Atualiza dados no banco
 * @param String table = nome da tabela
 * @param Array fields = campos a serem atualizados ["field" => value]
 * @param Array params = campos a serem filtrados ["field" => value]
 * @return Boolean
 */
function _updateData(string $table, array $fields, array $params) {
	try {
		$conn = _connect();
		return pg_update($conn, $table, $fields, $params);
	} catch (Exception $e) {
		throw new Exception("Update invalid! Error: ".$e->getMessage());
	} finally {
		pg_close($conn);
	}
}