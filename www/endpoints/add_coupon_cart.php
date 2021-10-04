<?php
require_once "../classes/class.addCoupon.inc";
// transforma o JSON enviado no params para um array
$params = json_decode($_REQUEST["params"], true);
$addCoupon = new addCoupon($params);
echo json_encode($addCoupon->executeAPI());