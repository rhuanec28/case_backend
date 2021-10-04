<?php
require_once "../environment/databaseUtils.php";
require_once "class.defaultAPI.inc";

class addItem extends defaultAPI {
    public function executeAPI() {
        if ($this->hasError()) {
            $this->setMessage("Params cannot be an empty array in: addItem API");
        } else if (!$this->checkItemExists()) {
            $this->setStatus(-2);
            $this->setMessage("Item does not exist in stock");
        } else if ($this->getParams("item_quantity") <= 0) {
            $this->setStatus(-3);
            $this->setMessage("Value 'item_quantity' cannot be 0 or less than 1");
        } else if (!$this->checkItemQuantityInStock()) {
            $this->setStatus(-4);
            $this->setMessage("Item quantity not available in stock");
        } else if (!$this->checkItemInCart()) {
            $this->setStatus(-5);
            $this->setMessage("Item already exists in cart");
        } else if (!$this->addItemToCart()) {
            $this->setStatus(-6);
            $this->setMessage("Could not add item to cart");
        } else {
            $this->setMessage("Item added successfully to cart");
            $this->setStatus(1);
        }

        return $this->_return();
    }

    /**
     * Verifica se o item existe no banco
     * @return Boolean
     */
    private function checkItemExists() {
        $sql = "SELECT 1 FROM ITEM WHERE CODE = $1";
        $bind = ["item_code" => $this->getParams("item_code")];
        return _recordExists($sql, $bind);
    }

    /**
     * Verifica se o carrinho existe no banco
     * @return Boolean
     */
    private function checkCartExists() {
        $sql = "SELECT 1 FROM CART WHERE USER_ID = $1";
        $bind = [
            "user_id" => $this->getParams("user_id")
        ];
        return _recordExists($sql, $bind);
    }

    /**
     * Verifica se o item possui a quantidade em estoque que está sendo adicionada
     * @return Boolean
     */
    private function checkItemQuantityInStock() {
        $sql = "SELECT 1 FROM ITEM WHERE STOCK >= $1 AND CODE = $2";
        $bind = [
            "item_quantity" => $this->getParams("item_quantity"),
            "code" => $this->getParams("item_code")
        ];

        return _recordExists($sql, $bind);
    }

    /**
     * Verifica se o item já está incluso no carrinho
     * @return Boolean
     */
    private function checkItemInCart() {
        //adiciona um novo carrinho, caso não exista
        if (!$this->checkCartExists()) {
            $this->newCart();
        }

        $sql = "SELECT 1 FROM CART_ITEM WHERE CART_ID = $1 AND ITEM_ID = $2";
        $bind = [
            "cart_id"  => $this->getCartId("user_id"),
            "item_id"  => $this->getItemId("item_code")
        ];
        return !_recordExists($sql, $bind);
    }

    /**
     * Cria um novo carrinho para o usuário/sessão fictício
     * @return Boolean
     */
    private function newCart() {
        $table = "cart";
        $insert = [
            "user_id" => $this->getParams("user_id")
        ];

        return _insertData($table, $insert);
    }

    /**
     * Adiciona o item ao carrinho
     * @return Boolean
     */
    private function addItemToCart() {
        $table = "cart_item";
        $insert = [
            "cart_id"  => $this->getCartId("user_id"),
            "item_id"  => $this->getItemId("item_code"),
            "quantity" => $this->getParams("item_quantity")
        ];

        return _insertData($table, $insert);
    }
}