#pragma once

#include "ethereal_device.h" 
#include "ethereal_swap_chain.h"
#include "ethereal_window.h"
#include "cassert"

//std
#include <memory>
#include <vector>

namespace ethereal {

	class EtherealRenderer {

	public:

		EtherealRenderer(EtherealWindow& window, EtherealDevice& device);
		~EtherealRenderer();

		EtherealRenderer(const EtherealRenderer&) = delete;
		EtherealRenderer& operator=(const EtherealRenderer&) = delete;

		bool isFrameInProgress() const { return isFrameStarted; }

		VkCommandBuffer getCurrentCommandBuffer() const { 
			assert(isFrameStarted && "Cannot get commandbuffer while frame not in progress");
			return commandBuffers[currentFrameIndex];
		}
		
		int getFrameIndex() const {
			assert(isFrameStarted && "Cannot get frame, its not in a progress");
			return currentFrameIndex;
		}
		VkRenderPass getSwapChainRenderPass() const { return etherealSwapChain->getRenderPass(); }

		VkCommandBuffer beginFrame();
		void endFrame();
		void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
		void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

	private:
		void createCommandBuffers();
		void freeCommandBuffers();
		void recreateSwapChain();
		 
		EtherealWindow& etherealWindow;
		EtherealDevice& etherealDevice;
		std::unique_ptr<EtherealSwapChain> etherealSwapChain;
		std::vector<VkCommandBuffer> commandBuffers;

		uint32_t currentImageIndex;
		int currentFrameIndex;
		bool isFrameStarted;
	};
}