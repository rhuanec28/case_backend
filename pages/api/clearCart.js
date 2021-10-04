const ClearCartAPI = async function (request, response) {
    const headers = { 'Content-Type': 'application/json' };
    const res = await fetch("http://localhost:80/endpoints/clear_cart.php", {
        method: 'POST',
        headers,
        body: JSON.stringify({
            query: request.query
        }),
    });
    const json = await res.json();

    if (json.errors) {
        response.json({});
        throw new Error('Failed to fetch Clear Cart API');
    }

    response.json(json);
}

export default ClearCartAPI;
