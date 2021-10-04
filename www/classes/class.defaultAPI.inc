<?php
class defaultAPI {
    private $message = "";
    private $status = 1;
    private $params = [];
    private $itemId;
    private $cartId;

    public function __construct($params) {
        if (empty($params)) {
            $this->setStatus(-1);
        }

        $this->setParams($params);
    }

    /**
     * Seta os parametros recebidos por GET
     * @param Array params - array com os parametros recebidos
     */
    public function setParams($params) {
        $this->params = $params;
    }

    /**
     * Retorna os parametros recebidos, ou apenas uma chave do array
     * @param String key - Chave a ser buscada no array
     * @return Array|String
     */
    public function getParams(string $key = "") {
        if ($key != "") {
            return $this->params[$key];
        }

        return $this->params;
    }

    /**
     * Seta a mensagem que irá ser retornada para a API
     * @param String message - mensagem que será exibida
     */
    public function setMessage(string $message) {
        $this->message = $message;
    }

    /**
     * Retorna a mensagem que irá ser exibida na API
     * @return String
     */
    public function getMessage() {
        return $this->message;
    }

    /**
     * Seta o status que irá ser retornado para a API
     * @param Int status - status que será exibido
     */
    public function setStatus(int $status) {
        $this->status = $status;
    }

    /**
     * Retorna o status que irá ser exibido na API
     * @return Integer
     */
    public function getStatus() {
        return $this->status;
    }

    /**
     * Verifica se existe algum erro ocorrido ao executar a API
     * @return Boolean
     */
    public function hasError() {
        return ($this->getStatus() != 1);
    }

    /**
     * Retorna o id do carrinho com base no usuário/sessão
     * @param String param - id do usuário
     */
    public function getCartId(string $param) {
        $cartId = "";

        if ($this->cartId != "") {
            return $this->cartId;
        }

        $sql = "SELECT ID FROM CART WHERE USER_ID = $1";
        $bind = [
            $param => $this->getParams($param)
        ];
        $data = _fetchData($sql, $bind);
        
        if ($data) {
            $cartId = $data[0]["id"];
            $this->setCartId($cartId);
        }

        return $cartId;
    }

    /**
     * Seta o id do carrinho, para evitar buscar no banco toda vez
     * @param String cartId - id do carrinho
     */
    private function setCartId(string $cartId) {
        $this->cartId = $cartId;
    }

    /**
     * Retorna o id do item com base no seu código
     * @param String param - código do item
     */
    public function getItemId(string $param) {
        $itemId = "";

        if ($this->itemId != "") {
            return $this->itemId;
        }

        $sql = "SELECT ID FROM ITEM WHERE CODE = $1";
        $bind = [
            $param => $this->getParams($param)
        ];
        $data = _fetchData($sql, $bind);
        
        if ($data) {
            $itemId = $data[0]["id"];
            $this->setItemId($itemId);
        }

        return $itemId;
    }

    /**
     * Seta o id do item, para evitar buscar no banco toda vez
     * @param String itemId - id do item
     */
    private function setItemId(string $itemId) {
        $this->itemId = $itemId;
    }

    /**
     * Retorna um array com o status e mensagem para ser retornada a API
     * @return Array
     */
    public function _return() {
        return [
            "status" => $this->getStatus(),
            "message" => $this->getMessage()
        ];
    }
}