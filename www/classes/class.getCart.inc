<?php
require_once "../environment/databaseUtils.php";
require_once "class.defaultAPI.inc";

class getCart extends defaultAPI {
    private $returnArr = [];

    public function executeAPI() {
        if ($this->hasError()) {
            $this->setMessage("Params cannot be an empty array in: getCart API");
        } else if (!$this->checkCartExists()) {
            $this->setStatus(-2);
            $this->setMessage("Cart does not exist");
        } else if (!$this->getCartData()) {
            $this->setStatus(-3);
            $this->setMessage("Cart is empty");
        } else {
            $this->setMessage("Cart information fetched successfully");
            $this->setStatus(1);
        }

        return $this->hasError() ? $this->_return() : $this->returnArr;
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
     * Retorna dados de um cupom
     * @return Array
     */
    public function getCouponData() {
        $sql = "SELECT 
                    C.CODE,
                    C.DISCOUNT 
                FROM COUPON C
                INNER JOIN CART CT 
                    ON CT.COUPON_ID = C.ID 
                WHERE CT.USER_ID = $1";
        $bind = [
            "user_id" => $this->getParams("user_id")
        ];
        $data = _fetchData($sql, $bind);
        return $data[0] ?? ["code" => "", "discount" => ""];
    }
    
    /**
     * Retorna os itens de um carrinho
     * @return Array
     */
    public function getCartItens() {
        $sql = "SELECT CI.QUANTITY, IT.PRICE, IT.CODE
                FROM ITEM IT 
                INNER JOIN CART_ITEM CI 
                    ON CI.ITEM_ID = IT.ID 
                INNER JOIN CART C
                    ON C.ID = CI.CART_ID
                WHERE C.USER_ID = $1";
        $bind = [
            "user_id" => $this->getParams("user_id")
        ];
        $data = _fetchData($sql, $bind);
        return $data ?? false;
    }

    /**
     * Atualiza a quantidade do item no carrinho
     * @return Boolean
     */
    private function getCartData() {
        $itens = $this->getCartItens();
        $couponData = $this->getCouponData();
        
        if (!$itens) {
            return false;
        }

        $itens = $this->getTotalValues($itens, $couponData["discount"]);

        // armazenando o retorno
        $this->returnArr["cartData"] = [
            "itens" => $itens,
            "coupon_discount" => $couponData["discount"],
            "coupon_code" => $couponData["code"],
            "totalItensValue" => $itens["totalItensValue"],
            "totalWithDiscount" => $itens["totalWithDiscount"]
        ];

        return true;
    }

    /**
     * Faz a multiplicação do valor e quantidade e coloca o total no array de itens
     * @param itens - contém todos os itens do carrinho e seus dados 
     * @return Array
     */
    private function getTotalValues($itens, $discount) {
        $cartTotal = 0;

        foreach ($itens as $key => $item) {
            // multiplica o valor de cada item por sua quantidade
            $itens[$key]["total"] = $item["quantity"] * $item["price"];
            // soma o total de cada item, para gerar o total do carrinho
            $cartTotal += $itens[$key]["total"];
        }

        $itens["totalItensValue"] = $cartTotal;
        // não calcula desconto caso não exista um cupom
        $itens["totalWithDiscount"] = !empty($discount) ? ($cartTotal - round($cartTotal * ($discount / 100), 2)) : $cartTotal;
        return $itens;
    }
}