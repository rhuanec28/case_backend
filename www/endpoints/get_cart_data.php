<?php
require_once "../classes/class.getCart.inc";
// transforma o JSON enviado no params para um array
$params = json_decode($_REQUEST["params"], true);
$getCart = new getCart($params);
echo json_encode($getCart->executeAPI());