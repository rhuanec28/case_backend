<?php
require_once "../environment/databaseUtils.php";
require_once "class.defaultAPI.inc";

class clearCart extends defaultAPI {
    public function executeAPI() {
        if ($this->hasError()) {
            $this->setMessage("Params cannot be an empty array in: clearCart API");
        } else if (!$this->checkCartExists()) {
            $this->setStatus(-2);
            $this->setMessage("Cart does not exist");
        } else if (!$this->clearCartCoupon()) {
            $this->setStatus(-3);
            $this->setMessage("Could not clear cart items");
        } else if (!$this->clearCartItens()) {
            $this->setStatus(-4);
            $this->setMessage("Could not clear cart coupon");
        } else {
            $this->setMessage("Cart cleared successfully");
            $this->setStatus(1);
        }

        return $this->_return();
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
     * Limpa o cupom do carrinho
     * @return Boolean
     */
    private function clearCartCoupon() {
        $table = "cart";
        $update = [
            "coupon_id"  => null
        ];
        $bind = [
            "id" => $this->getCartId("user_id")
        ];

        return _updateData($table, $update, $bind);
    }

    /**
     * Limpa os itens do carrinho
     * @return Boolean
     */
    private function clearCartItens() {
        $table = "cart_item";
        $bind = [
            "cart_id" => $this->getCartId("user_id")
        ];

        return _deleteData($table, $bind);
    }
}