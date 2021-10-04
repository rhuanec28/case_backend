<?php
class defaultAPI {
    private $message = "";
    private $status = 1;
    private $params = [];
    private $itemId;
    private $cartId;

    public function __construct(array $params) {
        if (empty($params)) {
            $this->setStatus(-1);
        }

        $this->setParams($params);
    }

    public function setParams(array $params) {
        $this->params = $params;
    }

    public function getParams(string $key = "") {
        if ($key != "") {
            return $this->params[$key];
        }

        return $this->params;
    }

    public function setMessage(string $message) {
        $this->message = $message;
    }

    public function getMessage() {
        return $this->message;
    }

    public function setStatus(int $status) {
        $this->status = $status;
    }

    public function getStatus() {
        return $this->status;
    }

    public function hasError() {
        return ($this->getStatus() != 1);
    }

    public function getCartId(string $param) {
        if ($this->cartId != "") {
            return $this->cartId;
        }

        $sql = "SELECT ID FROM CART WHERE USER_ID = $1";
        $bind = [$param => $this->getParams($param)];
        $data = _fetchData($sql, $bind);
        $cartId = $data[0]["id"];

        $this->setCartId($cartId);
        return $cartId;
    }

    private function setCartId(string $cartid) {
        $this->cartid = $cartid;
    }

    public function getItemId(string $param) {
        if ($this->itemId != "") {
            return $this->itemId;
        }

        $sql = "SELECT ID FROM ITEM WHERE CODE = $1";
        $bind = [$param => $this->getParams($param)];
        $data = _fetchData($sql, $bind);
        $itemId = $data[0]["id"];

        $this->setItemId($itemId);
        return $itemId;
    }

    private function setItemId(string $itemId) {
        $this->itemId = $itemId;
    }

    public function _return() {
        return [
            "status" => $this->getStatus(),
            "message" => $this->getMessage()
        ];
    }
}