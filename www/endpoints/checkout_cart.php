<?php
require_once "../classes/class.checkoutCart.inc";
// transforma o JSON enviado no params para um array
$params = json_decode($_REQUEST["params"], true);
$checkoutCart = new checkoutCart($params);
echo json_encode($checkoutCart->executeAPI());