<?php
class getCart {
    public function getCartData() {
        $cartData = ["teste" => "123"];
        $cartJson = json_encode($cartData);

        return $cartJson;
    }
}