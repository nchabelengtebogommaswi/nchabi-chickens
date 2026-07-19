#pragma once

struct SalesOrderItem
{
    int id{0};
    int salesOrderId{0};
    int productId{0};
    int quantity{0};
    double unitPrice{0.0};
    double lineTotal{0.0};
};
