--- a/drivers/net/wireless/orinoco/hw.c
+++ b/drivers/net/wireless/orinoco/hw.c
@@ -1093,7 +1093,11 @@
 		netdev_for_each_mc_addr(ha, dev) {
 			if (i == mc_count)
 				break;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 			memcpy(mclist.addr[i++], ha->addr, ETH_ALEN);
+#else
+			memcpy(mclist.addr[i++], ha->dmi_addr, ETH_ALEN);
+#endif
 		}
 
 		err = hw->ops->write_ltv(hw, USER_BAP,