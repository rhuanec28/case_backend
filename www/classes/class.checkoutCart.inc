<?php
require_once "../environment/databaseUtils.php";
require_once "class.defaultAPI.inc";

class checkoutCart extends defaultAPI {
    public function executeAPI() {
        if ($this->hasError()) {
            $this->setMessage("Params cannot be an empty array in: checkoutCart API");
        } else if (!$this->checkCartExists()) {
            $this->setStatus(-2);
            $this->setMessage("Cart does not exist");
        } else if (!$this->checkCartEmpty()) {
            $this->setStatus(-3);
            $this->setMessage("Cart is empty");
        } else if ($this->cartHasCoupon() && !$this->checkCouponExists()) {
            $this->setStatus(-4);
            $this->setMessage("Coupon invalid");
        } else if (!$this->checkItensInStock()) {
            $this->setStatus(-5);
            // a mensagem está definida dentro do método checkItensInStock
        } else {
            // faz a baixa no estoque
            $this->updateStock();
            // remove o carrinho do usuario para que os itens sejam liberados
            $this->removeCart();
            $this->setMessage("Cart checkout successful");
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
     * Verifica se o carrinho possui algum item vinculado
     * @return Boolean
     */
    private function checkCartEmpty() {
        $sql = "SELECT 1 
                FROM CART_ITEM CI 
                INNER JOIN CART C 
                    ON C.ID = CI.CART_ID 
                WHERE C.USER_ID = $1";
        $bind = [
            "user_id" => $this->getParams("user_id")
        ];
        return _recordExists($sql, $bind);
    }
    

    /**
     * Verifica se o cupom existe no banco
     * @return Boolean
     */
    private function cartHasCoupon() {
        $sql = "SELECT 1 FROM CART WHERE USER_ID = $1 AND COUPON_ID IS NOT NULL";
        $bind = [
            "user_id" => $this->getParams("user_id")
        ];
        return _recordExists($sql, $bind);
    }
    
    /**
     * Verifica se o cupom existe no banco
     * @return Boolean
     */
    private function checkCouponExists() {
        $sql = "SELECT 1 
                FROM COUPON CO 
                INNER JOIN CART C 
                    ON C.COUPON_ID = CO.ID AND C.COUPON_ID IS NOT NULL
                WHERE USER_ID = $1";
        $bind = [
            "user_id" => $this->getParams("user_id")
        ];
        return _recordExists($sql, $bind);
    }

    /**
     * Verifica se o item possui a quantidade em estoque
     * @return Boolean
     */
    private function checkItensInStock() {
        $sql = "SELECT I.CODE 
                FROM ITEM I
                INNER JOIN CART_ITEM CI
                    ON CI.ITEM_ID = I.ID
                INNER JOIN CART C
                    ON C.ID = CI.CART_ID
                WHERE CI.QUANTITY > I.STOCK
                    AND C.USER_ID = $1";
        $bind = [
            "user_id" => $this->getParams("user_id")
        ];

        $data = _fetchData($sql, $bind);
        if (!empty($data)) {
            $this->setMessage("Item ".$data[0]["code"]." does not have the desired quantity in stock");
            return false;
        }

        return true;
    }

    /**
     * Atualiza a quantidade do itens no estoque
     */
    private function updateStock() {
        $itens = $this->getCartItens();
        $table = "item";

        foreach ($itens as $item) {
            $newStock = $item["stock"] - $item["quantity"];
            $update = [
                "stock" => $newStock >= 0 ? $newStock : 0
            ];
            $bind = [
                "id"  => $item["item_id"]
            ];
            
            _updateData($table, $update, $bind);
        }
    }

    /**
     * Atualiza a quantidade do itens no estoque
     * @return Array
     */
    private function getCartItens() {
        $sql = "SELECT CI.QUANTITY, CI.ITEM_ID, I.STOCK
        FROM CART_ITEM CI
        INNER JOIN CART C
            ON C.ID = CI.CART_ID
        INNER JOIN ITEM I
            ON CI.ITEM_ID = I.ID
        WHERE C.USER_ID = $1";
        $bind = [
            "user_id" => $this->getParams("user_id")
        ];

        return _fetchData($sql, $bind);
    }
    
    /**
     * Remove os dados do carrinho
     */
    private function removeCart() {
        // remove os itens do carrinho
        $table = "cart_item";
        $bind = [
            "cart_id"  => $this->getCartId("user_id")
        ];
        _deleteData($table, $bind);

        // remove o carrinho
        $table = "cart";
        $bind = [
            "id"  => $this->getCartId("user_id")
        ];
        _deleteData($table, $bind);
    }
}