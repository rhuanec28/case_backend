<?php
require_once "../environment/databaseUtils.php";
require_once "class.defaultAPI.inc";

class removeItem extends defaultAPI {
    public function executeAPI() {
        if ($this->hasError()) {
            $this->setMessage("Params cannot be an empty array in: removeItem API");
        } else if (!$this->checkCartExists()) {
            $this->setStatus(-2);
            $this->setMessage("Cart does not exist");
        } else if (!$this->checkItemInCart()) {
            $this->setStatus(-3);
            $this->setMessage("Item does not exist in cart");
        } else if (!$this->removeItemFromCart()) {
            $this->setStatus(-4);
            $this->setMessage("Could not remove item from cart");
        } else {
            $this->setMessage("Item removed successfully from cart");
            $this->setStatus(1);
        }

        return $this->_return();
    }

    /**
     * Verifica se o item existe no banco
     * @return Boolean
     */
    private function checkItemInCart() {
        $sql = "SELECT 1 FROM CART_ITEM WHERE ITEM_ID = $1 AND CART_ID = $2";
        $bind = [
            "item_id"  => $this->getItemId("item_code"),
            "cart_id"  => $this->getCartId("user_id")
        ];
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
     * Remove o item do carrinho
     * @return Boolean
     */
    private function removeItemFromCart() {
        $table = "cart_item";
        $bind = [
            "cart_id"  => $this->getCartId("user_id"),
            "item_id"  => $this->getItemId("item_code")
        ];

        return _deleteData($table, $bind);
    }
}