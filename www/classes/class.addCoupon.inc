<?php
require_once "../environment/databaseUtils.php";
require_once "class.defaultAPI.inc";

class addCoupon extends defaultAPI {
    public function executeAPI() {
        if ($this->hasError()) {
            $this->setMessage("Params cannot be an empty array in: addCoupon API");
        } else if (!$this->checkCouponExists()) {
            $this->setStatus(-2);
            $this->setMessage("Coupon does not exist");
        } else if (!$this->addCouponToCart()) {
            $this->setStatus(-3);
            $this->setMessage("Could not add coupon to cart");
        } else {
            $this->setMessage("Coupon added successfully to cart");
            $this->setStatus(1);
        }

        return $this->_return();
    }

    /**
     * Verifica se o cupom existe no banco
     * @return Boolean
     */
    private function checkCouponExists() {
        $sql = "SELECT 1 FROM COUPON WHERE CODE = $1";
        $bind = ["coupon_code" => $this->getParams("coupon_code")];
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
     * Adiciona o cupom ao carrinho
     * @return Boolean
     */
    private function addCouponToCart() {
        if (!$this->checkCartExists()) {
            $this->newCart();
        }

        $table = "cart";
        $update = [
            "coupon_id"  => $this->getCouponId("coupon_code")
        ];
        $bind = [
            "id" => $this->getCartId("user_id")
        ];

        return _updateData($table, $update, $bind);
    }
    
    /**
     * Retorna o id do cupom com base no código
     * @return String
     */
    public function getCouponId(string $param) {
        $sql = "SELECT ID FROM COUPON WHERE CODE = $1";
        $bind = [
            $param => $this->getParams($param)
        ];
        $data = _fetchData($sql, $bind);
        $couponId = $data[0]["id"];

        return $couponId;
    }
}