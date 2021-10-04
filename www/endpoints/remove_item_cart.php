<?php
require_once "../classes/class.removeItem.inc";
// transforma o JSON enviado no params para um array
$params = json_decode($_REQUEST["params"], true);
$removeItem = new removeItem($params);
echo json_encode($removeItem->executeAPI());