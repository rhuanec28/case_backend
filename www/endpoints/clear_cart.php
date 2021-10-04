<?php
require_once "../classes/class.clearCart.inc";
// transforma o JSON enviado no params para um array
$params = json_decode($_REQUEST["params"], true);
$clearCart = new clearCart($params);
echo json_encode($clearCart->executeAPI());